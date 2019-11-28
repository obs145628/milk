//===--ast/ast-type-id.hh - ASTTypeId class definition ----------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTTypeId
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace cgen {

/// AST Node to represent a typename
/// Abstract class, doesn't do anything by itself
class ASTTypeId : public AST {
public:
  ASTTypeId(const obcl::Location &loc) : AST(loc) {}

private:
};

} // namespace cgen
