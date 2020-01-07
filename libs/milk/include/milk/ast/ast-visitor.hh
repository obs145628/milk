//===--ast/ast-visitor.hh - ASTVisitor class definition ---------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTVisitor
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast.hh"
#include "fwd.hh"

namespace milk {

/// Implementation of the visitor design pattern for the AST classes hierarchy
/// When called with an AST&, dispatch it to the visit method for the right type
/// The default implementation simply visit the children
/// You must create a child class, and override the visit methods
class ASTVisitor {
public:
  virtual ~ASTVisitor() = default;

  /// Performs dynamic dispatch of \p ast to the right visit() method
  void operator()(const AST &ast) { accept(ast); }

  /// Performs dynamic dispatch of \p ast to the right visit() method
  void accept(const AST &ast) { ast.accept(*this); }

  // default visitors, recursive call through children
  // virtual void visit(const ASTDefFun &ast);
  virtual void visit(const ASTDefAlias &ast);
  virtual void visit(const ASTDefEnum &ast);
  virtual void visit(const ASTDefFun &ast);
  virtual void visit(const ASTDefStruct &ast);
  virtual void visit(const ASTDefVar &ast);
  virtual void visit(const ASTExprCall &ast);
  virtual void visit(const ASTExprConstructor &ast);
  virtual void visit(const ASTExprField &ast);
  virtual void visit(const ASTExprId &ast);
  virtual void visit(const ASTExprNumber &ast);
  virtual void visit(const ASTExprSpecial &ast);
  virtual void visit(const ASTNamedStorage &ast);
  virtual void visit(const ASTProgram &ast);
  virtual void visit(const ASTStmtBlock &ast);
  virtual void visit(const ASTStmtBreak &ast);
  virtual void visit(const ASTStmtExpr &ast);
  virtual void visit(const ASTStmtIf &ast);
  virtual void visit(const ASTStmtReturn &ast);
  virtual void visit(const ASTStmtVar &ast);
  virtual void visit(const ASTStmtWhile &ast);
  virtual void visit(const ASTTypeLabelName &ast);
  virtual void visit(const ASTTypeLabelRef &ast);

private:
};

} // namespace milk
