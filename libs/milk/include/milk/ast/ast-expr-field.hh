//===--ast/ast-expr-field.hh - ASTExprField class definition -----*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprField
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "obcl/lexer/token.hh"
#include <cassert>

namespace milk {

/// AST node for a field access expression
/// val.<fieldname>
class ASTExprField : public ASTExpr {
public:
  ASTExprField(const obcl::Location &loc, ASTExprPtr &&val,
               const std::string &field)
      : ASTExpr(loc), _val(std::move(val)), _field(field) {}

  ASTExprField(ASTExprPtr &&val, const obcl::Token &field)
      : ASTExprField(obcl::Location(val->loc(), field.loc), std::move(val),
                     field.val) {
    assert(field.type == obcl::TOK_ID);
  }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &val() const { return *_val; }
  const std::string &field() const { return _field; }

private:
  ASTExprPtr _val;
  std::string _field;
};

} // namespace milk
