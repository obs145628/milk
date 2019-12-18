//===--ast/ast-stmt-if.hh - ASTStmtIf class definition -----------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtIf
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement If/Else Node
/// The else is optional, but parser replace it by '{}' if ignored
class ASTStmtIf : public ASTStmt {
public:
  /// @param beg_loc location of 'if'
  ASTStmtIf(const obcl::Location &beg_loc, ASTExprPtr &&cond,
            ASTStmtPtr &&if_stmt, ASTStmtPtr &&else_stmt)
      : ASTStmt(obcl::Location(beg_loc, else_stmt->loc())),
        _cond(std::move(cond)), _if_stmt(std::move(if_stmt)),
        _else_stmt(std::move(else_stmt)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &cond() const { return *_cond; }
  const ASTStmt &if_stmt() const { return *_if_stmt; }
  const ASTStmt &else_stmt() const { return *_else_stmt; }

private:
  ASTExprPtr _cond;
  ASTStmtPtr _if_stmt;
  ASTStmtPtr _else_stmt;
};

} // namespace milk
