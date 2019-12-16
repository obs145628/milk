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
#include <utility>
#include <vector>

#define FORWARD_AST(NAME)                                                      \
  class NAME;                                                                  \
  using NAME##Ptr = std::unique_ptr<NAME>;

namespace milk {

FORWARD_AST(AST)
FORWARD_AST(ASTDef)
FORWARD_AST(ASTDefAlias)
FORWARD_AST(ASTDefFun)
FORWARD_AST(ASTNamedStorage)
FORWARD_AST(ASTProgram)
FORWARD_AST(ASTStmt)
FORWARD_AST(ASTTypeLabel)
FORWARD_AST(ASTTypeLabelName)
FORWARD_AST(ASTTypeLabelRef)

class ASTVisitor;

using named_ast_types_t = std::vector<std::pair<std::string, ASTTypeLabelPtr>>;

} // namespace milk

#undef FORWARD_AST
