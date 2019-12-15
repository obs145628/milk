//===--ast/ast-type-label.hh - ASTTypeLabel class definition ----*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTTypeLabel
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace milk {

/// AST Node to reference a type (eg i16, &u8, &[] i32, etc)
class ASTTypeLabel : public AST {
public:
  ASTTypeLabel(const obcl::Location &loc) : AST(loc) {}

private:
};

} // namespace milk
