//===--ast/fwd.hh - AST forward definition ----------------------*- C++ -*-===//
//
// cgen representation compiler library
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

namespace cgen {

FORWARD_AST(AST)
FORWARD_AST(ASTDef)
FORWARD_AST(ASTDefFun)
FORWARD_AST(ASTDefStruct)
FORWARD_AST(ASTDefType)
FORWARD_AST(ASTDefVar)
FORWARD_AST(ASTExpr)
FORWARD_AST(ASTExprBinOp)
FORWARD_AST(ASTExprCall)
FORWARD_AST(ASTExprCast)
FORWARD_AST(ASTExprField)
FORWARD_AST(ASTExprFloat)
FORWARD_AST(ASTExprId)
FORWARD_AST(ASTExprInt)
FORWARD_AST(ASTExprSizeof)
FORWARD_AST(ASTExprString)
FORWARD_AST(ASTExprUnOp)
FORWARD_AST(ASTInstr)
FORWARD_AST(ASTInstrBlock)
FORWARD_AST(ASTInstrBreak)
FORWARD_AST(ASTInstrContinue)
FORWARD_AST(ASTInstrExpr)
FORWARD_AST(ASTInstrIf)
FORWARD_AST(ASTInstrReturn)
FORWARD_AST(ASTInstrVar)
FORWARD_AST(ASTInstrWhile)
FORWARD_AST(ASTProgram)
FORWARD_AST(ASTTypeId)
FORWARD_AST(ASTTypeIdName)
FORWARD_AST(ASTTypeIdPointer)

using ast_args_def_t = std::vector<std::pair<ASTTypeIdPtr, std::string>>;
using ast_instrs_list_t = std::vector<ASTInstrPtr>;
using ast_exprs_list_t = std::vector<ASTExprPtr>;

class ASTVisitor;

} // namespace cgen

#undef FORWARD_AST
