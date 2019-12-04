//===--ctranslator/ctranslator.hh - CTranslator class definition *- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class CTranslator
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../ast/ast-visitor.hh"
#include "../ast/fwd.hh"
#include <ostream>
#include <set>
#include <string>

namespace cgen {

/// class to ouput C code from the cgen AST
/// Can manually add code before / after
/// Only output a single C file
/// Based on the visitor design pattern
class CTranslator : public ASTVisitor {
public:
  /// @param os the stream where the C output code will be written
  CTranslator(std::ostream &os);

  /// add an include command at the beginning of the file
  /// @param sys - if true, use '<path>', otherwhise '"path"'
  void add_header(const std::string &path, bool sys = true);

  /// add some specific code at the beginning of the file
  /// (after the includes)
  void extend_preface(const std::string &code);

  /// visit the AST and output C code to the stream
  void compile(const ASTProgram &ast);

  void visit(const ASTDefFun &ast) override;
  void visit(const ASTDefStruct &ast) override;
  void visit(const ASTDefType &ast) override;
  void visit(const ASTDefVar &ast) override;
  void visit(const ASTExprBinOp &ast) override;
  void visit(const ASTExprCall &ast) override;
  void visit(const ASTExprCast &ast) override;
  void visit(const ASTExprField &ast) override;
  void visit(const ASTExprFloat &ast) override;
  void visit(const ASTExprId &ast) override;
  void visit(const ASTExprInt &ast) override;
  void visit(const ASTExprSizeof &ast) override;
  void visit(const ASTExprString &ast) override;
  void visit(const ASTExprUnOp &ast) override;
  void visit(const ASTInstrBlock &ast) override;
  void visit(const ASTInstrBreak &ast) override;
  void visit(const ASTInstrContinue &ast) override;
  void visit(const ASTInstrExpr &ast) override;
  void visit(const ASTInstrIf &ast) override;
  void visit(const ASTInstrReturn &ast) override;
  void visit(const ASTInstrVar &ast) override;
  void visit(const ASTInstrWhile &ast) override;
  void visit(const ASTProgram &ast) override;
  void visit(const ASTTypeIdName &ast) override;
  void visit(const ASTTypeIdPointer &ast) override;

private:
  std::ostream &_os;

  void _disp_function(const ASTDefFun &ast, bool disp_body);

  void _dump_preface();

  std::set<std::string> _headers;
  std::set<std::string> _headers_sys;

  std::string _preface;
};

} // namespace cgen
