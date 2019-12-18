//===--ast/ast-stmt-expr.hh - ASTStmtExpr class definition -------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtExpr
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement Expr Node, only contains a single expression, it's value is
/// ignored
class ASTStmtExpr : public ASTStmt {
public:
  /// @param end_loc location of ';'
  ASTStmtExpr(const obcl::Location &end_loc, ASTExprPtr &&expr)
      : ASTStmt(obcl::Location(expr->loc(), end_loc)), _expr(std::move(expr)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &expr() const { return *_expr; }

private:
  ASTExprPtr _expr;
};

} // namespace milk
