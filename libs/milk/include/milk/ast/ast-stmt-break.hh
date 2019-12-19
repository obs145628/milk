//===--ast/ast-stmt-break.hh - ASTStmtBreak class definition -----*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmtBreak
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Statement Break Node
/// Represents a break or continue statement, to control posiiton in loop
class ASTStmtBreak : public ASTStmt {
public:
  enum class Kind { BREAK, CONTINUE };

  /// @param beg_loc location of 'break/continue'
  /// @param end_loc location of ';'
  ASTStmtBreak(const obcl::Location &beg_loc, const obcl::Location &end_loc,
               Kind kind)
      : ASTStmt(obcl::Location(beg_loc, end_loc)), _kind(kind) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }

private:
  Kind _kind;
};

} // namespace milk
