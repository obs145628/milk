//===--ast/ast-expr-number.hh - ASTExprNumber class definition --*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprNumber
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"
#include <cassert>
#include <cstdint>

namespace milk {

/// AST node for constant number
/// int or float constant
class ASTExprNumber : public AST {
public:
  enum class Kind { U64, F64, CHAR };

  ASTExprNumber(const obcl::Location &loc, Kind kind, std::uint64_t val)
      : AST(loc), _kind(kind), _v_int(val) {
    assert(kind == Kind::U64 || kind == Kind::CHAR);
  }

  ASTExprNumber(const obcl::Location &loc, Kind kind, double val)
      : AST(loc), _kind(kind), _v_float(val) {
    assert(kind == Kind::F64);
  }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }

  std::uint64_t get_u64() const {
    assert(_kind == Kind::U64);
    return _v_int;
  }

  double get_f64() const {
    assert(_kind == Kind::F64);
    return _v_float;
  }

  char get_char() const {
    assert(_kind == Kind::CHAR);
    return _v_int;
  }

private:
  Kind _kind;

  union {
    std::uint64_t _v_int;
    double _v_float;
  };
};

} // namespace milk
