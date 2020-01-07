//===--ast/ast-expr-constructor.hh - ASTExprCallNamed class -----*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprConstructor
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include <string>

namespace milk {

/// AST node for a call with named parameters
/// eg: foo(a: 8, b: 7, ...)
/// Right now, only used for struct creation
/// StructName (field1: val1, field2: val2, ...)
/// Later, may be combined with ASTExprCall
class ASTExprCallNamed : public ASTExpr {
public:
  ASTExprCallNamed(const obcl::Location &loc, ASTExprPtr &&callee,
                   ast_exprs_dict_t &&args)
      : ASTExpr(loc), _callee(std::move(callee)), _args(std::move(args)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &callee() const { return *_callee; }
  const ast_exprs_dict_t &args() const { return _args; }

private:
  ASTExprPtr _callee;
  ast_exprs_dict_t _args;
};

} // namespace milk
