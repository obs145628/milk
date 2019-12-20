//===--ast/ast-expr-id.hh - ASTExprId class definition ----------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprId
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "obcl/lexer/token.hh"
#include <cassert>

namespace milk {

/// AST node for an expression identifier
/// (eg: var name, function)
class ASTExprId : public ASTExpr {
public:
  ASTExprId(const obcl::Token &tok) : ASTExpr(tok.loc), _id(tok.val) {
    assert(tok.type == obcl::TOK_ID);
  }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &id() const { return _id; }

private:
  std::string _id;
};

} // namespace milk
