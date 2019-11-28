//===--ast/ast-expr-cast.hh - ASTExprCast class definition -------*- C++-*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprCast
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"

namespace cgen {

/// AST node that represents a cast expression
/// Cast a expression to a different type
/// static, ptr, or repinterpret
/// More infos in cgen definitions
class ASTExprCast : public ASTExpr {
public:
  enum class Kind {
    STATIC,
    PTR,
    REINTERPRET,
  };

  ///
  /// @param beg_loc location of the first token of the parsed function
  /// @param end_loc location of the last token of the parsed function
  /// @param kind kind of cast
  /// @param type typename of the expression after casting
  /// @param expr the expression to be casted
  ASTExprCast(const obcl::Location &beg_loc, const obcl::Location &end_loc,
              Kind kind, ASTTypeIdPtr &&type, ASTExprPtr &&expr)
      : ASTExpr(obcl::Location(beg_loc, end_loc)), _kind(kind),
        _type(std::move(type)), _expr(std::move(expr)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  const ASTTypeId &type() const { return *_type; }
  const ASTExpr &expr() const { return *_expr; }

private:
  Kind _kind;
  ASTTypeIdPtr _type;
  ASTExprPtr _expr;
};

} // namespace cgen
