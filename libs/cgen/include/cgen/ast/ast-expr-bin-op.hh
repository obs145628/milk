//===--ast/ast-expr-binop.hh - ASTExprBinop class definition ----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprBinop
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"

namespace cgen {

/// AST Node for a binary operator expression
class ASTExprBinOp : public ASTExpr {

public:
  enum class Op {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    EQ,
    NEQ,
    GT,
    LT,
    GEQ,
    LEQ,
    AND,
    OR,
    BAND,
    BOR,
    BXOR,
    BLS,
    BRS,
    ASSIGN,
  };

  ASTExprBinOp(Op op, ASTExprPtr &&left, ASTExprPtr &&right)
      : ASTExpr(obcl::Location(left->loc(), right->loc())), _op(op),
        _left(std::move(left)), _right(std::move(right)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Op op() const { return _op; }
  const ASTExpr &left() const { return *_left; }
  const ASTExpr &right() const { return *_right; }

  static const char *op2str(Op op) {
    switch (op) {
    case Op::ADD:
      return "+";
    case Op::SUB:
      return "-";
    case Op::MUL:
      return "*";
    case Op::DIV:
      return "/";
    case Op::MOD:
      return "%";
    case Op::EQ:
      return "==";
    case Op::NEQ:
      return "!=";
    case Op::GT:
      return ">";
    case Op::LT:
      return "<";
    case Op::GEQ:
      return ">=";
    case Op::LEQ:
      return "<=";
    case Op::AND:
      return "&&";
    case Op::OR:
      return "||";
    case Op::BAND:
      return "&";
    case Op::BOR:
      return "|";
    case Op::BXOR:
      return "^";
    case Op::BLS:
      return "<<";
    case Op::BRS:
      return ">>";
    case Op::ASSIGN:
      return "=";
    default:
      return "???";
    }
  }

private:
  Op _op;
  ASTExprPtr _left;
  ASTExprPtr _right;
};

} // namespace cgen
