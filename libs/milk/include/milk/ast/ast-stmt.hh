//===--ast/ast-stmt.hh - ASTStmt class definition ----------------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTStmt
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace milk {

/// AST Statement class
/// Abstract Parent class for al; statements (loops, if, return, block, etc)
class ASTStmt : public AST {
public:
  ASTStmt(const obcl::Location &loc) : AST(loc) {}

private:
};

} // namespace milk
