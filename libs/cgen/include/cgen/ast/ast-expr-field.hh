//===--ast/ast-expr-field.hh - ASTExprField class definition ----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprField
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"
#include "obcl/lexer/token.hh"
#include <string>

namespace cgen {

/// AST Node for field acces
/// <expr>.field
class ASTExprField : public ASTExpr {

public:
  ASTExprField(ASTExprPtr &&left, const obcl::Token &field)
      : ASTExpr(obcl::Location(left->loc(), field.loc)), _left(std::move(left)),
        _field(field.val) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &left() const { return *_left; }
  const std::string &field() const { return _field; }

private:
  ASTExprPtr _left;
  std::string _field;
};

} // namespace cgen
