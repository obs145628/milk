//===--ast/ast-def-fun.hh - ASTDefFun class definition -----------------*- C++
//-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTDef
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace milk {

/// Represent a function definition in milk language, with its prototype and its
/// body
class ASTDefFun : public AST {
public:
  ASTDef(const obcl::Location &loc) : AST(loc) {}

private:
};

} // namespace milk
