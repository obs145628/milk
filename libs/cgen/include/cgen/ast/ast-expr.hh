//===--ast/ast-expr.hh - ASTExpr class definition ---------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExpr
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace cgen {

/// AST Node for an expression (has a value)
/// Abstract class, doesn't do anything by itself
/// Only used to have a base class for all expressions
class ASTExpr : public AST {
public:
  ASTExpr(const obcl::Location &loc) : AST(loc) {}
};
} // namespace cgen
