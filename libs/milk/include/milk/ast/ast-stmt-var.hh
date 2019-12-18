//===--ast/ast-stmt-var.hh - ASTStmtVar class definition ---------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtVar
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement Variable Node
/// Define and initialize a local scoped variable
class ASTStmtVar : public ASTStmt {
public:
  /// @param beg_loc location of 'let' or 'const'
  /// @param end_loc location of ';'
  ASTStmtVar(const obcl::Location &beg_loc, const obcl::Location &end_loc,
             ASTNamedStoragePtr &&storage, ASTExprPtr &&init)
      : ASTStmt(obcl::Location(beg_loc, end_loc)), _storage(std::move(storage)),
        _init(std::move(init)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTNamedStorage &storage() const { return *_storage; }
  const ASTExpr &init() const { return *_init; }

private:
  ASTNamedStoragePtr _storage;
  ASTExprPtr _init;
};

} // namespace milk
