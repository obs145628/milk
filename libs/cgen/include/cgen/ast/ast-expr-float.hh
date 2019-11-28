//===--ast/ast-expr-float.hh - ASTExprFloat class definition ----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprFloat
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"
#include "obcl/lexer/token.hh"

namespace cgen {

/// ASTNode for a float constant expression
/// May be float or double
class ASTExprFloat : public ASTExpr {

public:
  enum class Type { F32, F64 };

  ASTExprFloat(const obcl::Token &tok, Type type)
      : ASTExpr(tok.loc), _val(tok.get_float()), _type(type) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  std::uint16_t val() const { return _val; }
  Type type() const { return _type; }

  static const char *type2str(Type type) {
    switch (type) {
    case Type::F32:
      return "float";
    case Type::F64:
      return "double";
    default:
      return "???";
    }
  }

private:
  double _val;
  Type _type;
};

} // namespace cgen
