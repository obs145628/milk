//===--ast/ast-def.hh - ASTDef class definition -----------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTDef
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace cgen {

/// Parent class for all the definitions in the AST (struct, fun, type, etc)
/// Does nothing, simply used to have a base class for all definitions
class ASTDef : public AST {
public:
  ASTDef(const obcl::Location &loc) : AST(loc) {}

private:
};

} // namespace cgen
