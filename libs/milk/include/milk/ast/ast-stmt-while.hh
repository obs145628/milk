//===--ast/ast-stmt-while.hh - ASTStmtWhile class definition -----*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtWhile
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement While Node
/// Represents a while loop statement
class ASTStmtWhile : public ASTStmt {
public:
  /// @param beg_loc location of 'while'
  ASTStmtWhile(const obcl::Location &beg_loc, ASTExprPtr &&cond,
               ASTStmtPtr &&body)
      : ASTStmt(obcl::Location(beg_loc, body->loc())), _cond(std::move(cond)),
        _body(std::move(body)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &cond() const { return *_cond; }
  const ASTStmt &body() const { return *_body; }

private:
  ASTExprPtr _cond;
  ASTStmtPtr _body;
};

} // namespace milk
