//===--ast/ast-instr.hh - ASTInstr class definition --------------*-C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstr
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"

namespace cgen {
/// AST Node that represent an instruction
/// Abstract class, does nothing by itself
/// Used only to have a type for all instructions
class ASTInstr : public AST {
public:
  ASTInstr(const obcl::Location &loc) : AST(loc) {}

private:
};
} // namespace cgen
