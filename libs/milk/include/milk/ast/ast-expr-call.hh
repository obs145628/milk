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
