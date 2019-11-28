//===--ast/ast-expr-un-op.hh - ASTExprUnOp class definition -----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprUnOp
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"

namespace cgen {

/// AST Node for an unary operand expression
class ASTExprUnOp : public ASTExpr {
public:
  enum class Op { NEG, NOT, BNOT, ADDR, DEREF };

  ///
  /// @param beg_loc location of the first token of the parsed nod
  // @param op operator
  // @param right operand
  ASTExprUnOp(const obcl::Location &beg_loc, Op op, ASTExprPtr &&right)
      : ASTExpr(obcl::Location(beg_loc, right->loc())), _op(op),
        _right(std::move(right)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Op op() const { return _op; }
  const ASTExpr &right() const { return *_right; }

  static const char *op2str(Op op) {
    switch (op) {
    case Op::NEG:
      return "-";
    case Op::NOT:
      return "!";
    case Op::BNOT:
      return "~";
    case Op::ADDR:
      return "&";
    case Op::DEREF:
      return "*";
    default:
      return "???";
    }
  }

private:
  Op _op;
  ASTExprPtr _right;
};

} // namespace cgen
