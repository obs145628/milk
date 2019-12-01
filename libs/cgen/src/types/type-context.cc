#include "types/type-context.hh"
#include "ast/all.hh"
#include "obcl/utils/format-string.hh"
#include "types/type-builder.hh"
#include "types/type-check.hh"
#include "types/type-context.hh"
#include "types/type-error.hh"
#include "types/type-fun.hh"
#include "types/type-infos.hh"
#include "types/type-numeric.hh"
#include "types/type-ptr.hh"
#include "types/type-ref.hh"
#include "types/type-struct.hh"
#include <cassert>

namespace cgen {

TypeContext::TypeContext()
    : _res_expr(nullptr), _res_typeid(nullptr), _curr_fundef(nullptr),
      _curr_loop(nullptr) {
  _add_native_defs();
}

void TypeContext::build(const ASTProgram &ast) {
  std::vector<const ASTDefFun *> dfuns;
  std::vector<const ASTDefStruct *> dstructs;
  std::vector<const ASTDefType *> dtypes;
  std::vector<const ASTDefVar *> dvars;
  for (const auto &def : ast.defs()) {
    if (auto def_fun = dynamic_cast<const ASTDefFun *>(def.get()))
      dfuns.push_back(def_fun);
    else if (auto def_struct = dynamic_cast<const ASTDefStruct *>(def.get()))
      dstructs.push_back(def_struct);
    else if (auto def_type = dynamic_cast<const ASTDefType *>(def.get()))
      dtypes.push_back(def_type);
    else if (auto def_var = dynamic_cast<const ASTDefVar *>(def.get()))
      dvars.push_back(def_var);
  }

  for (auto st : dstructs)
    _struct_decl(*st);
  for (auto alias : dtypes)
    _alias_def(*alias);
  for (auto var : dvars)
    _global_decl(*var);
  for (auto fun : dfuns)
    _fun_decl(*fun);
  for (auto st : dstructs)
    _struct_def(*st);
  for (auto var : dvars)
    _global_def(*var);
  for (auto fun : dfuns)
    _fun_def(*fun);
}

const Type *TypeContext::type_of_typeid(const ASTTypeId &ast) {
  auto it = _type_typeids.find(&ast);
  if (it != _type_typeids.end())
    return it->second;

  _res_typeid = nullptr;
  accept(ast);
  assert(_res_typeid);
  auto res = _res_typeid;
  _res_typeid = nullptr;
  _type_typeids.emplace(&ast, res);
  return res;
}

const Type *TypeContext::type_of_exp(const ASTExpr &ast) {
  auto it = _type_exprs.find(&ast);
  if (it != _type_exprs.end())
    return it->second;

  _res_expr = nullptr;
  accept(ast);
  assert(_res_expr);
  auto res = _res_expr;
  _res_expr = nullptr;
  _type_exprs.emplace(&ast, res);
  return res;
}

void TypeContext::visit(const ASTExprCall &ast) {
  const auto &callee = ast.callee();
  auto callee_name = dynamic_cast<const ASTExprId *>(&callee);
  if (!callee_name)
    throw std::runtime_error{"TypeContext: call: callee"
                             " must be an id"};

  const auto &name = callee_name->name();

  auto it = _fundefs.find(name);
  if (_fundefs.find(name) == _fundefs.end())
    throw TypeError(callee, "expr_call", "function not found");
  auto type = it->second.type;
  if (type->args().size() != ast.args().size())
    throw TypeError(ast, "expr_call",
                    FORMAT_STRING("expected "
                                  << type->args().size() << " arguments, got "
                                  << ast.args().size() << "argument"));

  for (std::size_t i = 0; i < type->args().size(); ++i) {
    auto arg_type = type->args()[i];
    auto val_type = type_of_exp(*ast.args()[i]);
    _verify_type(arg_type, val_type, *ast.args()[i], "expr_call");
  }

  _res_expr = type->ret();
}

void TypeContext::visit(const ASTExprCast &ast) {
  auto dst_type = type_of_typeid(ast.type());
  auto src_type = type_of_exp(ast.expr());

  switch (ast.kind()) {

  case ASTExprCast::Kind::STATIC: {
    auto src_vtype = type_infos::to_val(src_type);
    if (!type_infos::is_numeric(*src_vtype) ||
        !type_infos::is_numeric(*dst_type))
      throw TypeError(ast, "expr_cast_static",
                      "both src and dst types must be numeric");
    _res_expr = dst_type;
    break;
  }

  case ASTExprCast::Kind::REINTERPRET: {
    auto src_vtype = type_infos::to_val(src_type);
    int src_size = type_infos::size(src_vtype);
    int dst_size = type_infos::size(dst_type);
    if (src_size == -1 || dst_size == -1 || src_size != dst_size)
      throw TypeError(ast, "expr_cast_reinterpret", "Data type sizes differ");

    _res_expr = type_infos::is_ref(*src_type)
                    ? TypeBuilder::instance().ref(dst_type)
                    : dst_type;
    break;
  }

  case ASTExprCast::Kind::PTR: {
    auto src_vtype = type_infos::to_val(src_type);
    if (!type_infos::is_ptr(*src_vtype) || !type_infos::is_ptr(*dst_type))
      throw TypeError(ast, "expr_cast_ptr",
                      "Both src and dst must be ptr types");

    _res_expr = type_infos::is_ref(*src_type)
                    ? TypeBuilder::instance().ref(dst_type)
                    : dst_type;
    break;
  }
  };
}

void TypeContext::visit(const ASTExprField &ast) {
  auto var_type = type_of_exp(ast.left());
  auto var_vtype = type_infos::to_val(var_type);
  auto var_st = dynamic_cast<const TypeStruct *>(var_vtype);
  if (!var_st)
    throw TypeError(ast, "expr_field", "left operand must be a struct");
  assert(var_st->defined());

  auto it = var_st->fields().find(ast.field());
  if (it == var_st->fields().end())
    throw TypeError(ast, "expr_field",
                    FORMAT_STRING("struct " << var_st->name() << " has no field"
                                            << ast.field()));

  auto field_type = it->second;
  if (type_infos::is_ref(*var_type))
    _res_expr = TypeBuilder::instance().ref(field_type);
  else
    _res_expr = field_type;
}

void TypeContext::visit(const ASTExprFloat &ast) {
  switch (ast.type()) {
  case ASTExprFloat::Type::F32:
    _res_expr = TypeBuilder::instance().f32();
    break;
  case ASTExprFloat::Type::F64:
    _res_expr = TypeBuilder::instance().f64();
    break;
  }
}

void TypeContext::visit(const ASTExprId &ast) {
  const auto &name = ast.name();
  const Type *type = nullptr;
  if (auto it = _curr_fundef->scope.find(name); it != _curr_fundef->scope.end())
    type = it->second;
  else if (auto it = _globals.find(name); it != _globals.end())
    type = it->second;

  if (!type)
    throw TypeError(ast, "expr_id", "variable not found");

  _res_expr = TypeBuilder::instance().ref(type);
}

void TypeContext::visit(const ASTExprInt &ast) {
  switch (ast.type()) {
  case ASTExprInt::Type::U8:
    _res_expr = TypeBuilder::instance().u8();
    break;
  case ASTExprInt::Type::U16:
    _res_expr = TypeBuilder::instance().u16();
    break;
  case ASTExprInt::Type::U32:
    _res_expr = TypeBuilder::instance().u32();
    break;
  case ASTExprInt::Type::U64:
    _res_expr = TypeBuilder::instance().u64();
    break;
  case ASTExprInt::Type::I8:
    _res_expr = TypeBuilder::instance().i8();
    break;
  case ASTExprInt::Type::I16:
    _res_expr = TypeBuilder::instance().i16();
    break;
  case ASTExprInt::Type::I32:
    _res_expr = TypeBuilder::instance().i32();
    break;
  case ASTExprInt::Type::I64:
    _res_expr = TypeBuilder::instance().i64();
    break;
  }
}

void TypeContext::visit(const ASTExprSizeof &ast) {
  accept(ast.type());
  _res_expr = type_infos::type_usize();
}

void TypeContext::visit(const ASTExprString &) {
  _res_expr = TypeBuilder::instance().ptr(type_infos::type_char());
}

void TypeContext::visit(const ASTInstrBlock &ast) {
  _ret_end = false;
  for (const auto &ins : ast.instrs())
    accept(*ins);
}

void TypeContext::visit(const ASTInstrBreak &ast) {
  if (!_curr_loop)
    throw TypeError(ast, "instr_break", "Break outside of loop");
  _loop_break.emplace(&ast, _curr_loop);
  _ret_end = false;
}

void TypeContext::visit(const ASTInstrContinue &ast) {
  if (!_curr_loop)
    throw TypeError(ast, "instr_continue", "Continue outside of loop");
  _loop_con.emplace(&ast, _curr_loop);
  _ret_end = false;
}

void TypeContext::visit(const ASTInstrExpr &ast) {
  accept(ast.expr());
  _ret_end = false;
}

void TypeContext::visit(const ASTInstrIf &ast) {
  auto type_cond = type_of_exp(ast.cond());
  _verify_type(type_infos::type_bool(), type_cond, ast.cond(), "instr_if");

  accept(ast.instr_if());
  bool left_end = _ret_end;
  accept(ast.instr_else());
  bool right_end = _ret_end;
  _ret_end = left_end && right_end;
}

void TypeContext::visit(const ASTInstrReturn &ast) {
  auto ret_type = _curr_fundef->type->ret();
  auto exp_type = ast.has_expr() ? type_of_exp(ast.val())
                                 : TypeBuilder::instance().type_void();
  _verify_type(ret_type, exp_type, ast, "instr_return");
  _ret_end = true;
}

void TypeContext::visit(const ASTInstrVar &ast) {
  assert(_curr_fundef);
  const auto &name = ast.name();
  auto &scope = _curr_fundef->scope;
  if (scope.find(name) != scope.end())
    throw TypeError(ast, "instr_var",
                    "There is already a variable with this name");

  _ret_end = false;
  auto type = type_of_typeid(ast.type());
  scope.emplace(name, type);
}

void TypeContext::visit(const ASTInstrWhile &ast) {
  _ret_end = false;
  auto old_loop = _curr_loop;
  _curr_loop = &ast;

  auto type_cond = type_of_exp(ast.cond());
  _verify_type(type_infos::type_bool(), type_cond, ast.cond(), "instr_while");

  accept(ast.body());

  _curr_loop = old_loop;
}

void TypeContext::visit(const ASTTypeIdName &ast) {
  auto it = _named_types.find(ast.name());
  if (it == _named_types.end())
    throw TypeError(ast, "typeid_name", "Unknown type name");
  _res_typeid = it->second;
}

void TypeContext::visit(const ASTTypeIdPointer &ast) {
  auto type = type_of_typeid(ast.type());
  _res_typeid = TypeBuilder::instance().ptr(type);
}

void TypeContext::_add_native_defs() {
  _named_types.emplace("void", TypeBuilder::instance().type_void());
  _named_types.emplace("u8", TypeBuilder::instance().u8());
  _named_types.emplace("u16", TypeBuilder::instance().u16());
  _named_types.emplace("u32", TypeBuilder::instance().u32());
  _named_types.emplace("u64", TypeBuilder::instance().u64());
  _named_types.emplace("i8", TypeBuilder::instance().i8());
  _named_types.emplace("i16", TypeBuilder::instance().i16());
  _named_types.emplace("i32", TypeBuilder::instance().i32());
  _named_types.emplace("i64", TypeBuilder::instance().i64());
  _named_types.emplace("f32", TypeBuilder::instance().f32());
  _named_types.emplace("f64", TypeBuilder::instance().f64());

  _named_types.emplace("bool", type_infos::type_bool());
  _named_types.emplace("char", type_infos::type_char());
  _named_types.emplace("isize", type_infos::type_isize());
  _named_types.emplace("usize", type_infos::type_usize());
}

void TypeContext::_struct_decl(const ASTDefStruct &ast) {
  const auto &name = ast.name();

  if (_named_types.find(name) != _named_types.end())
    throw TypeError(ast, "struct_decl",
                    "There is already a type with this name");

  auto type = TypeBuilder::instance().type_struct(name);
  _named_types.emplace(name, type);
}

void TypeContext::_struct_def(const ASTDefStruct &ast) {
  const auto &name = ast.name();
  auto it = _named_types.find(name);
  assert(it != _named_types.end());
  auto type = it->second;
  auto type_s = dynamic_cast<const TypeStruct *>(type);
  assert(type_s);
  std::map<std::string, const Type *> fields;

  for (const auto &f : ast.fields()) {
    auto f_type = type_of_typeid(*f.first);
    const auto &f_name = f.second;
    fields.emplace(f_name, f_type);
  }

  type_s->make_def(fields);
}

void TypeContext::_global_decl(const ASTDefVar &ast) {
  const auto &name = ast.name();
  if (_globals.find(name) != _globals.end())
    throw TypeError(ast, "global_decl",
                    "There is already a global variable with this name");

  auto type = type_of_typeid(ast.type());
  _globals.emplace(name, type);
}

void TypeContext::_global_def(const ASTDefVar &ast) {
  auto it = _globals.find(ast.name());
  assert(it != _globals.end());
  auto type = it->second;
  if (!ast.has_val())
    return;

  auto val_type = type_of_exp(ast.val());
  _verify_type(type, val_type, ast, "global_def");
}

void TypeContext::_alias_def(const ASTDefType &ast) {
  const auto &alias = ast.alias();
  if (_named_types.find(alias) != _named_types.end())
    throw TypeError(ast, "alias_def", "There is already a type with this name");

  auto type = type_of_typeid(ast.type());
  _named_types.emplace(alias, type);
}

void TypeContext::_fun_decl(const ASTDefFun &ast) {
  if (_fundefs.find(ast.name()) != _fundefs.end())
    throw TypeError(ast, "fun_cld",
                    "There is already a function with this name");

  auto ret = type_of_typeid(ast.ret_type());
  std::vector<const Type *> args;
  for (const auto &arg : ast.args())
    args.push_back(type_of_typeid(*arg.first));

  auto type = TypeBuilder::instance().fun(ret, args);
  auto type_f = dynamic_cast<const TypeFun *>(type);
  assert(type_f);
  Fundef fun;
  fun.name = ast.name();
  fun.type = type_f;
  _fundefs.emplace(ast.name(), fun);
}

void TypeContext::_fun_def(const ASTDefFun &ast) {
  if (!ast.has_body())
    return;

  auto it = _fundefs.find(ast.name());
  assert(it != _fundefs.end());
  auto &fun = it->second;

  _curr_fundef = &fun;
  auto &scope = _curr_fundef->scope;

  for (const auto &arg : ast.args()) {
    scope.emplace(arg.second, type_of_typeid(*arg.first));
  }

  accept(ast.body());
  _curr_fundef = nullptr;

  bool has_ret = _ret_end;
  if (!has_ret && !type_infos::is_void(*fun.type->ret()))
    throw TypeError(ast, "function_def", "no return value");
}

void TypeContext::_verify_type(const Type *expect, const Type *act,
                               const AST &node, const std::string &fn) {
  if (!type_check::match(expect, act))
    throw TypeMismatchError(node, fn, expect, act);
}

void TypeContext::_verify_binop(const Type *arg1, const Type *arg2,
                                const Type *op1, const Type *op2,
                                const AST &node, const std::string &fn) {
  _verify_type(arg1, op1, node, fn);
  _verify_type(arg2, op2, node, fn);
}

} // namespace cgen
