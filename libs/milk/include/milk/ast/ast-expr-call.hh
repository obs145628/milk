//===--ast/ast-expr-call.hh - ASTExprCall class definition ------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprCall
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include <cassert>

namespace milk {

/// AST node for a call expression
/// calle (args...)
/// The called is usually a funciton or method, but can be any object with
/// operator overloading
/// Other types of expression are converted to call expression during parsing:
/// unary and binary operators (except && and ||)
/// subscript operator
class ASTExprCall : public ASTExpr {
public:
  static constexpr const char *OP_SET = "@op:set";
  static constexpr const char *OP_SETADD = "@op:setadd";
  static constexpr const char *OP_SETSUB = "@op:setsub";
  static constexpr const char *OP_SETMUL = "@op:setmul";
  static constexpr const char *OP_SETDIV = "@op:setdiv";
  static constexpr const char *OP_SETMOD = "@op:setmod";
  static constexpr const char *OP_BOR = "@op:bor";
  static constexpr const char *OP_BXOR = "@op:bxor";
  static constexpr const char *OP_BAND = "@op:band";
  static constexpr const char *OP_EQ = "@op:eq";
  static constexpr const char *OP_NE = "@op:ne";
  static constexpr const char *OP_LT = "@op:lt";
  static constexpr const char *OP_GT = "@op:gt";
  static constexpr const char *OP_LE = "@op:le";
  static constexpr const char *OP_GE = "@op:ge";
  static constexpr const char *OP_LSHIFT = "@op:lshift";
  static constexpr const char *OP_RSHIFT = "@op:rshift";
  static constexpr const char *OP_ADD = "@op:add";
  static constexpr const char *OP_SUB = "@op:sub";
  static constexpr const char *OP_MUL = "@op:mul";
  static constexpr const char *OP_DIV = "@op:div";
  static constexpr const char *OP_MOD = "@op:mod";
  static constexpr const char *OP_POS = "@op:pos";
  static constexpr const char *OP_NEG = "@op:neg";
  static constexpr const char *OP_BNOT = "@op:bnot";
  static constexpr const char *OP_NOT = "@op:not";
  static constexpr const char *OP_SUBSCRIPT = "@op:subscript";

  ASTExprCall(const obcl::Location &loc, ASTExprPtr &&callee,
              ast_exprs_list_t &&args)
      : ASTExpr(loc), _callee(std::move(callee)), _args(std::move(args)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &callee() const { return *_callee; }
  const ast_exprs_list_t &args() const { return _args; }

private:
  ASTExprPtr _callee;
  ast_exprs_list_t _args;
};

} // namespace milk
