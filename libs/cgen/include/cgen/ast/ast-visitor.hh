//===--ast/ast-visitor.hh - ASTVisitor class definition ---------*- C++ -*-===//
//
// cgen representation compiler library
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

namespace cgen {

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
  virtual void visit(const ASTDefFun &ast);
  virtual void visit(const ASTDefStruct &ast);
  virtual void visit(const ASTDefType &ast);
  virtual void visit(const ASTDefVar &ast);
  virtual void visit(const ASTExprBinOp &ast);
  virtual void visit(const ASTExprCall &ast);
  virtual void visit(const ASTExprCast &ast);
  virtual void visit(const ASTExprField &ast);
  virtual void visit(const ASTExprFloat &ast);
  virtual void visit(const ASTExprId &ast);
  virtual void visit(const ASTExprInt &ast);
  virtual void visit(const ASTExprSizeof &ast);
  virtual void visit(const ASTExprString &ast);
  virtual void visit(const ASTExprUnOp &ast);
  virtual void visit(const ASTInstrBlock &ast);
  virtual void visit(const ASTInstrBreak &ast);
  virtual void visit(const ASTInstrContinue &ast);
  virtual void visit(const ASTInstrExpr &ast);
  virtual void visit(const ASTInstrIf &ast);
  virtual void visit(const ASTInstrReturn &ast);
  virtual void visit(const ASTInstrVar &ast);
  virtual void visit(const ASTInstrWhile &ast);
  virtual void visit(const ASTProgram &ast);
  virtual void visit(const ASTTypeIdName &ast);
  virtual void visit(const ASTTypeIdPointer &ast);

private:
};

} // namespace cgen
