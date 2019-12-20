//===--ast/ast-expr-special.hh - ASTExprSpecial class -----------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprSpecial
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include <cassert>

namespace milk {

/// AST node for a special operator expression
/// These are for the operators with a behavior that cannot be expressed by a
/// function call.
/// These usually are short-circuit operators
class ASTExprSpecial : public ASTExpr {
public:
  enum class Kind { OP_AND, OP_OR, OP_TERNARY };

  ASTExprSpecial(const obcl::Location &loc, Kind kind,
                 ast_exprs_list_t &&operands)
      : ASTExpr(loc), _kind(kind), _operands(std::move(operands)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  const ast_exprs_list_t &operands() const { return _operands; }

private:
  Kind _kind;
  ast_exprs_list_t _operands;
};

} // namespace milk
