#include "ast/all.hh"
#include "types/type-builder.hh"
#include "types/type-context.hh"
#include "types/type-error.hh"
#include "types/type-infos.hh"
#include "types/type-numeric.hh"
#include "types/type-ptr.hh"
#include "types/type-ref.hh"
#include <cassert>

namespace cgen {

void TypeContext::visit(const ASTExprUnOp &ast) {
  auto arg_type = type_of_exp(ast.right());
  auto arg_vtype = type_infos::to_val(arg_type);

  switch (ast.op()) {
  case ASTExprUnOp::Op::NEG:
    if (type_infos::is_numeric(*arg_vtype))
      _res_expr = arg_vtype;
    else
      throw TypeError(ast, "unop:-", "operand must be a numeric");
    break;

  case ASTExprUnOp::Op::NOT:
    if (dynamic_cast<const type_infos::TypeBool *>(arg_vtype))
      _res_expr = type_infos::type_bool();
    else
      throw TypeError(ast, "unop:!", "operand must be a bool");
    break;

  case ASTExprUnOp::Op::BNOT:
    if (type_infos::is_int(*arg_vtype))
      _res_expr = arg_vtype;
    else
      throw TypeError(ast, "unop:-", "operand must be an integer");
    break;

  case ASTExprUnOp::Op::ADDR:
    if (auto ref_type = dynamic_cast<const TypeRef *>(arg_type);
        ref_type != nullptr)
      _res_expr = TypeBuilder::instance().ptr(ref_type->type());
    else
      throw TypeError(ast, "unop:&", "operand must be a reference");
    break;

  case ASTExprUnOp::Op::DEREF:
    if (auto ptr_type = dynamic_cast<const TypePtr *>(arg_vtype);
        ptr_type != nullptr)
      _res_expr = TypeBuilder::instance().ref(ptr_type->type());
    else
      throw TypeError(ast, "unop:*",
                      "operand must be a pointer, but is of type " +
                          arg_type->to_str());
    break;
  };
}

} // namespace cgen
