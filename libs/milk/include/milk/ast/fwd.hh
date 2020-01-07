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
FORWARD_AST(ASTExpr)
FORWARD_AST(ASTExprCall)
FORWARD_AST(ASTExprCallNamed)
FORWARD_AST(ASTExprField)
FORWARD_AST(ASTExprId)
FORWARD_AST(ASTExprNumber)
FORWARD_AST(ASTExprSpecial)
FORWARD_AST(ASTNamedStorage)
FORWARD_AST(ASTProgram)
FORWARD_AST(ASTStmt)
FORWARD_AST(ASTStmtBlock)
FORWARD_AST(ASTStmtBreak)
FORWARD_AST(ASTStmtExpr)
FORWARD_AST(ASTStmtIf)
FORWARD_AST(ASTStmtReturn)
FORWARD_AST(ASTStmtVar)
FORWARD_AST(ASTStmtWhile)
FORWARD_AST(ASTTypeLabel)
FORWARD_AST(ASTTypeLabelName)
FORWARD_AST(ASTTypeLabelRef)

class ASTVisitor;

using ast_storage_list_t = std::vector<ASTNamedStoragePtr>;
using ast_defs_list_t = std::vector<ASTDefPtr>;
using ast_stmts_list_t = std::vector<ASTStmtPtr>;
using ast_exprs_list_t = std::vector<ASTExprPtr>;
using ast_exprs_dict_t = std::vector<std::pair<std::string, ASTExprPtr>>;

} // namespace milk

#undef FORWARD_AST
