//===--ast/ast-expr.hh - ASTExpr class definition ---------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExpr
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace milk {

/// Parent class for all the expressions
/// All expressions have a value of known type, including void (no value)
/// Abstract class, children are commons expressions such as function call,
/// constants
class ASTExpr : public AST {
public:
  ASTExpr(const obcl::Location &loc) : AST(loc) {}

private:
};

} // namespace milk
