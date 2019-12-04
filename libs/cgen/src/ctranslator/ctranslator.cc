#include "ctranslator/ctranslator.hh"
#include "ast/all.hh"

#define BOOL_OP_OR_FN "__cgen_bool_or_op_special"
#define BOOL_OP_AND_FN "__cgen_bool_and_op_special"

namespace {

const char *BASE_HEADERS_SYS[] = {"stddef.h", "stdint.h"};

const char *BASE_PREFACE_TYPEDEFS = ""
                                    "typedef uint8_t u8;\n"
                                    "typedef uint16_t u16;\n"
                                    "typedef uint32_t u32;\n"
                                    "typedef uint64_t u64;\n"
                                    "typedef int8_t i8;\n"
                                    "typedef int16_t i16;\n"
                                    "typedef int32_t i32;\n"
                                    "typedef int64_t i64;\n"
                                    "typedef float f32;\n"
                                    "typedef double f64;\n"
                                    "typedef int64_t isize;\n"
                                    "typedef uint64_t usize;\n"
                                    "typedef int32_t bool;\n"
                                    "\n";

const char *BASE_PREFACE_FUNCTIONS =
    ""
    "static inline bool " BOOL_OP_OR_FN "(bool x, bool y) {\n"
    "  return x || y;\n"
    "}\n"
    "\n"
    "static inline bool " BOOL_OP_AND_FN "(bool x, bool y) {\n"
    "  return x && y;\n"
    "}\n"
    "\n";

} // namespace

namespace cgen {

CTranslator::CTranslator(std::ostream &os) : _os(os), _preface() {
  for (std::size_t i = 0;
       i < sizeof(BASE_HEADERS_SYS) / sizeof(BASE_HEADERS_SYS[0]); ++i)
    _headers_sys.insert(BASE_HEADERS_SYS[i]);
  extend_preface(BASE_PREFACE_TYPEDEFS);
  extend_preface(BASE_PREFACE_FUNCTIONS);
}

void CTranslator::add_header(const std::string &path, bool sys) {
  if (sys)
    _headers_sys.insert(path);
  else
    _headers.insert(path);
}

void CTranslator::extend_preface(const std::string &code) { _preface += code; }

void CTranslator::compile(const ASTProgram &ast) {

  // ==== PRINT ORDER ===
  // preface

  // forward struct defs
  // type aliases
  // forward var defs
  // struct defs
  // forward function defs
  // var defs
  // function defs

  // end

  _dump_preface();

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

  _os << "// == Forward struct definitions ==" << std::endl;
  for (auto st : dstructs)
    _os << "typedef struct " << st->def_name() << " " << st->name() << ";"
        << std::endl;
  _os << std::endl;

  _os << "// == Type aliases ==" << std::endl;
  for (auto alias : dtypes)
    accept(*alias);
  _os << std::endl;

  _os << "// == Forward variable definitions ==" << std::endl;
  for (auto dv : dvars) {
    _os << "extern ";
    accept(dv->type());
    _os << " " << dv->name() << ";" << std::endl;
  }
  _os << std::endl;

  _os << "// == Struct definitions ==" << std::endl;
  for (auto st : dstructs) {
    accept(*st);
    _os << std::endl;
  }
  _os << std::endl;

  _os << "// == Forward function definitions ==" << std::endl;
  for (auto df : dfuns)
    _disp_function(*df, false);
  _os << std::endl;

  _os << "// == Variable definitions ==" << std::endl;
  for (auto dv : dvars)
    accept(*dv);
  _os << std::endl;

  _os << "// == Function definitions ==" << std::endl;
  for (auto df : dfuns)
    _disp_function(*df, true);
  _os << std::endl;
}

void CTranslator::visit(const ASTDefFun &) {
  throw std::runtime_error(
      "CTranslator::visit(ASTDefFun&) shouldn't be called");
}

void CTranslator::visit(const ASTDefStruct &ast) {
  _os << "struct " << ast.def_name() << " {" << std::endl;
  for (const auto &field : ast.fields()) {
    _os << "  ";
    accept(*field.first);
    _os << " " << field.second << ";" << std::endl;
  }

  _os << "};" << std::endl;
}

void CTranslator::visit(const ASTDefType &ast) {
  _os << "typedef ";
  accept(ast.type());
  _os << " " << ast.alias() << ";" << std::endl;
}

void CTranslator::visit(const ASTDefVar &ast) {
  accept(ast.type());
  _os << " " << ast.name();

  if (ast.has_val()) {
    _os << " = ";
    accept(ast.val());
  }
  _os << ";" << std::endl;
}

void CTranslator::visit(const ASTExprBinOp &ast) {
  if (ast.op() == ASTExprBinOp::Op::AND || ast.op() == ASTExprBinOp::Op::OR) {
    _os << (ast.op() == ASTExprBinOp::Op::AND ? BOOL_OP_AND_FN : BOOL_OP_OR_FN)
        << "(";
    accept(ast.left());
    _os << ", ";
    accept(ast.right());
    _os << ")";
  }

  else {
    _os << "(";
    accept(ast.left());
    _os << ") " << ASTExprBinOp::op2str(ast.op()) << " (";
    accept(ast.right());
    _os << ")";
  }
}

void CTranslator::visit(const ASTExprCall &ast) {
  _os << "(";
  accept(ast.callee());
  _os << ")(";

  const auto &args = ast.args();
  for (std::size_t i = 0; i < args.size(); ++i) {
    accept(*args[i]);
    if (i + 1 < args.size())
      _os << ", ";
  }

  _os << ")";
}

void CTranslator::visit(const ASTExprCast &ast) {
  // TODO: only works for kind == static
  _os << "(";
  accept(ast.type());
  _os << ") (";
  accept(ast.expr());
  _os << ")";
}

void CTranslator::visit(const ASTExprField &ast) {
  _os << "(";
  accept(ast.left());
  _os << ")." << ast.field();
}

void CTranslator::visit(const ASTExprFloat &ast) {
  _os << "(" << ASTExprFloat::type2str(ast.type()) << ") " << ast.val();
}

void CTranslator::visit(const ASTExprId &ast) { _os << ast.name(); }

void CTranslator::visit(const ASTExprInt &ast) {
  _os << "(" << ASTExprInt::type2str(ast.type()) << ") " << ast.val();
}

void CTranslator::visit(const ASTExprSizeof &ast) {
  _os << "sizeof(";
  accept(ast.type());
  _os << ")";
}

void CTranslator::visit(const ASTExprString &ast) {
  _os << '"' << ASTExprString::encode(ast.val()) << '"';
}

void CTranslator::visit(const ASTExprUnOp &ast) {
  _os << ASTExprUnOp::op2str(ast.op()) << "(";
  accept(ast.right());
  _os << ")";
}

void CTranslator::visit(const ASTInstrBlock &ast) {
  _os << "{" << std::endl;
  for (const auto &ins : ast.instrs()) {
    accept(*ins);
    _os << std::endl;
  }
  _os << "}" << std::endl;
}

void CTranslator::visit(const ASTInstrBreak &) { _os << "break;"; }

void CTranslator::visit(const ASTInstrContinue &) { _os << "continue;"; }

void CTranslator::visit(const ASTInstrExpr &ast) {
  accept(ast.expr());
  _os << ";";
}

void CTranslator::visit(const ASTInstrIf &ast) {
  _os << "if (";
  accept(ast.cond());
  _os << ") ";
  accept(ast.instr_if());
  _os << " else ";
  accept(ast.instr_else());
}

void CTranslator::visit(const ASTInstrReturn &ast) {
  _os << "return";
  if (ast.has_expr()) {
    _os << " ";
    accept(ast.val());
  }
  _os << ";";
}

void CTranslator::visit(const ASTInstrVar &ast) {
  accept(ast.type());
  _os << " " << ast.name() << ";";
}

void CTranslator::visit(const ASTInstrWhile &ast) {
  _os << "while (";
  accept(ast.cond());
  _os << ")" << std::endl;
  accept(ast.body());
}

void CTranslator::visit(const ASTProgram &) {
  throw std::runtime_error("CTranslator::visit(ASTProgram&) "
                           "shouldn't be called");
}

void CTranslator::visit(const ASTTypeIdName &ast) { _os << ast.name(); }

void CTranslator::visit(const ASTTypeIdPointer &ast) {
  accept(ast.type());
  _os << " *";
}

void CTranslator::_disp_function(const ASTDefFun &ast, bool disp_body) {
  if (disp_body && !ast.has_body())
    return;

  accept(ast.ret_type());
  _os << " " << ast.name() << "(";
  const auto &args = ast.args();
  for (std::size_t i = 0; i < args.size(); ++i) {
    accept(*args[i].first);
    _os << " " << args[i].second;
    if (i + 1 < args.size())
      _os << ", ";
  }
  _os << ")";

  if (disp_body) {
    _os << std::endl;
    accept(ast.body());
    _os << std::endl;
  } else
    _os << ";";
  _os << std::endl;
}

void CTranslator::_dump_preface() {

  // print includes
  for (const auto &h : _headers_sys)
    _os << "#include <" << h << '>' << std::endl;
  for (const auto &h : _headers)
    _os << "#include \"" << h << '"' << std::endl;
  _os << std::endl;

  _os << _preface << std::endl;
}

} // namespace cgen
