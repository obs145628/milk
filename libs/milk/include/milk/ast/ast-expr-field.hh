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
/// val::<field>
class ASTExprField : public ASTExpr {
public:
  enum class Kind {
    FD_STRUCT,
    FD_MOD,
  };

  ASTExprField(const obcl::Location &loc, Kind kind, ASTExprPtr &&val,
               const std::string &field)
      : ASTExpr(loc), _kind(kind), _val(std::move(val)), _field(field) {}

  ASTExprField(Kind kind, ASTExprPtr &&val, const obcl::Token &field)
      : ASTExprField(obcl::Location(val->loc(), field.loc), kind,
                     std::move(val), field.val) {
    assert(field.type == obcl::TOK_ID);
  }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  const ASTExpr &val() const { return *_val; }
  const std::string &field() const { return _field; }

private:
  Kind _kind;
  ASTExprPtr _val;
  std::string _field;
};

} // namespace milk
