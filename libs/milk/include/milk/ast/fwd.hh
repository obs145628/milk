//===--ast/fwd.hh - AST forward definition ----------------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contain forward definition of all AST classes, and other helper
/// types
///
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <string>
#include <vector>

#define FORWARD_AST(NAME)                                                      \
  class NAME;                                                                  \
  using NAME##Ptr = std::unique_ptr<NAME>;

namespace milk {

FORWARD_AST(AST)
FORWARD_AST(ASTDef)
FORWARD_AST(ASTDefAlias)
FORWARD_AST(ASTDefEnum)
FORWARD_AST(ASTDefFun)
FORWARD_AST(ASTDefStruct)
FORWARD_AST(ASTDefVar)
FORWARD_AST(ASTNamedStorage)
FORWARD_AST(ASTProgram)
FORWARD_AST(ASTStmt)
FORWARD_AST(ASTTypeLabel)
FORWARD_AST(ASTTypeLabelName)
FORWARD_AST(ASTTypeLabelRef)

class ASTVisitor;

using ast_storage_list_t = std::vector<ASTNamedStoragePtr>;
using ast_defs_list_t = std::vector<ASTDefPtr>;

} // namespace milk

#undef FORWARD_AST
