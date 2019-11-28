//===--ast/ast-expr-id.hh - ASTExprId class definition ----------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprId
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"
#include "obcl/lexer/token.hh"
#include <string>

namespace cgen {

/// AST Node class for an identifier expression
/// (var name, fun name, etc)
class ASTExprId : public ASTExpr {

public:
  ASTExprId(const obcl::Token &tok) : ASTExpr(tok.loc), _name(tok.val) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }

private:
  std::string _name;
};

} // namespace cgen
