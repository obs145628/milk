//===--ast/ast-expr-int.hh - ASTExprInt class definition --------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprInt
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"
#include "obcl/lexer/token.hh"
#include <cstdint>

namespace cgen {

/// AST Node class for integer constant expression
/// Can be from 8/16/32 or 64 bytes, signed or unsigned
class ASTExprInt : public ASTExpr {

public:
  enum class Type { U8, U16, U32, U64, I8, I16, I32, I64 };

  ASTExprInt(const obcl::Token &tok, Type type)
      : ASTExpr(tok.loc), _val(tok.get_int()), _type(type) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  std::uint16_t val() const { return _val; }
  Type type() const { return _type; }

  static const char *type2str(Type type) {
    switch (type) {
    case Type::U8:
      return "uint8_t";
    case Type::U16:
      return "uint16_t";
    case Type::U32:
      return "uint32_t";
    case Type::U64:
      return "uint64_t";
    case Type::I8:
      return "int8_t";
    case Type::I16:
      return "int16_t";
    case Type::I32:
      return "int32_t";
    case Type::I64:
      return "int64_t";
    default:
      return "???";
    }
  }

private:
  std::uint64_t _val;
  Type _type;
};

} // namespace cgen
