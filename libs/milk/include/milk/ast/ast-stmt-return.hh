//===--ast/ast-stmt-return.hh - ASTStmtReturn class definition ---*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtReturn
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement Return Node
/// Represents a return statement, with an optional return value
class ASTStmtReturn : public ASTStmt {
public:
  /// @param beg_loc location of 'return'
  /// @param end_loc location of ';'
  ASTStmtReturn(const obcl::Location &beg_loc, const obcl::Location &end_loc,
                ASTExprPtr &val)
      : ASTStmt(obcl::Location(beg_loc, end_loc)), _val(std::move(val)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  bool has_val() const { return _val.get() != nullptr; }
  const ASTExpr &val() const { return *_val; }

private:
  ASTExprPtr _val;
};

} // namespace milk
