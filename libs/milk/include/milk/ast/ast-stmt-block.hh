//===--ast/ast-stmt-block.hh - ASTStmtBlock class definition -----*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtBlock
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement Block Node, represent multiple statements regrouped in one
/// All statements belong to a scope
class ASTStmtBlock : public ASTStmt {
public:
  /// @param beg_loc location of '{'
  /// @param end_loc location of '}'
  ASTStmtBlock(const obcl::Location &beg_loc, const obcl::Location &end_loc,
               ast_stmts_list_t &&stmts)
      : ASTStmt(obcl::Location(beg_loc, end_loc)), _stmts(std::move(stmts)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ast_stmts_list_t &stmts() const { return _stmts; }

private:
  ast_stmts_list_t _stmts;
};

} // namespace milk
