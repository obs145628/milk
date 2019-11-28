//===--ast/ast-instr-expr.hh - ASTInstrExpr class definition -----*-C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrExpr
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST Node instruction which is one expression
class ASTInstrExpr : public ASTInstr {
public:
  /// @param end_loc - location of ';'
  ASTInstrExpr(const obcl::Location &end_loc, ASTExprPtr &&expr)
      : ASTInstr(obcl::Location(expr->loc(), end_loc)), _expr(std::move(expr)) {
  }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &expr() const { return *_expr; }

private:
  ASTExprPtr _expr;
};

} // namespace cgen
