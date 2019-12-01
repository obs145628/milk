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

void TypeContext::visit(const ASTExprBinOp &ast) {
  auto left_type = type_of_exp(ast.left());
  auto left_vtype = type_infos::to_val(left_type);
  auto right_type = type_of_exp(ast.right());

  switch (ast.op()) {
  case ASTExprBinOp::Op::ADD:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:+(num, num)");
      _res_expr = left_vtype;
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, type_infos::type_isize(), left_type, right_type,
                    ast, "binop:+(ptr, isize)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:+", "Invalid types for operator +");
    break;

  case ASTExprBinOp::Op::SUB:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:-(num, num)");
      _res_expr = left_vtype;
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, type_infos::type_isize(), left_type, right_type,
                    ast, "binop:-(ptr, isize)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:-", "Invalid types for operator -");
    break;

  case ASTExprBinOp::Op::MUL:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:*(num, num)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:*", "Invalid types for operator *");
    break;

  case ASTExprBinOp::Op::DIV:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:/(num, num)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:*", "Invalid types for operator /");
    break;

  case ASTExprBinOp::Op::MOD:
    if (type_infos::is_int(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:%(int, int)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:%", "Invalid types for operator %");
    break;

  case ASTExprBinOp::Op::EQ:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:==(num, num)");
      _res_expr = type_infos::type_bool();
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:==(ptr, ptr)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:==", "Invalid types for operator ==");
    break;

  case ASTExprBinOp::Op::NEQ:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:!=(num, num)");
      _res_expr = type_infos::type_bool();
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:!=(ptr, ptr)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:!=", "Invalid types for operator !=");
    break;

  case ASTExprBinOp::Op::GT:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:>(num, num)");
      _res_expr = type_infos::type_bool();
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:>(ptr, ptr)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:>", "Invalid types for operator >");
    break;

  case ASTExprBinOp::Op::LT:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:<(num, num)");
      _res_expr = type_infos::type_bool();
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:<(ptr, ptr)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:<", "Invalid types for operator <");
    break;

  case ASTExprBinOp::Op::GEQ:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:>=(num, num)");
      _res_expr = type_infos::type_bool();
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:>=(ptr, ptr)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:>=", "Invalid types for operator >=");
    break;

  case ASTExprBinOp::Op::LEQ:
    if (type_infos::is_numeric(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:<=(num, num)");
      _res_expr = type_infos::type_bool();
    } else if (type_infos::is_ptr(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:<=(ptr, ptr)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:<=", "Invalid types for operator <=");
    break;

  case ASTExprBinOp::Op::AND:
    if (dynamic_cast<const type_infos::TypeBool *>(left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:&&(bool, bool)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:&&",
                      "Invalid types for operator &&: " + left_vtype->to_str() +
                          ", " + right_type->to_str());
    break;

  case ASTExprBinOp::Op::OR:
    if (dynamic_cast<const type_infos::TypeBool *>(left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:||(bool, bool)");
      _res_expr = type_infos::type_bool();
    } else
      throw TypeError(ast, "binop:||", "Invalid types for operator ||");
    break;

  case ASTExprBinOp::Op::BAND:
    if (type_infos::is_int(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:&(int, int)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:&", "Invalid types for operator &");
    break;

  case ASTExprBinOp::Op::BOR:
    if (type_infos::is_int(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:|(int, int)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:|", "Invalid types for operator |");
    break;

  case ASTExprBinOp::Op::BXOR:
    if (type_infos::is_int(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:^(int, int)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:^", "Invalid types for operator ^");
    break;

  case ASTExprBinOp::Op::BLS:
    if (type_infos::is_int(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:<<(int, int)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:<<", "Invalid types for operator <<");
    break;

  case ASTExprBinOp::Op::BRS:
    if (type_infos::is_int(*left_vtype)) {
      _verify_binop(left_vtype, left_vtype, left_type, right_type, ast,
                    "binop:>>(int, int)");
      _res_expr = left_vtype;
    } else
      throw TypeError(ast, "binop:>>", "Invalid types for operator ??");
    break;

  case ASTExprBinOp::Op::ASSIGN:

    if (type_infos::is_ref(*left_type)) {
      _verify_binop(left_type, left_vtype, left_type, right_type, ast,
                    "binop:=(t&, t)");
      _res_expr = TypeBuilder::instance().type_void();
    } else
      throw TypeError(ast, "binop:=", "Invalid types for operator =");
    break;
  }
}

} // namespace cgen
