//===--parser/parser.hh - Parser class definition ---------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class Parser
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../ast/fwd.hh"
#include "lexer.hh"
#include "obcl/parser/parser.hh"

namespace cgen {

/// Parser for cgen language
/// Read many source files / raw code
/// Parse and combine all definitions in one AST
class Parser : public obcl::Parser {

public:
  Parser();

  /// Parse every definition of a file cgen source file
  void parse_file(const std::string &path);

  /// Parve every definition of a raw cgen source code
  void parse_string(const std::string &str);

  ASTProgram *ast() { return _main_ast.get(); }

private:
  ASTProgramPtr _main_ast;

  ASTProgramPtr _program();

  ASTDefPtr _def();
  ASTDefFunPtr _fundef();
  ASTDefStructPtr _structdef();
  ASTDefTypePtr _typedef();
  ASTDefVarPtr _vardef();
  ast_args_def_t _fieldsdef();

  ASTInstrPtr _instr();
  ASTInstrBlockPtr _instrblock();
  ASTInstrBreakPtr _instrbreak();
  ASTInstrContinuePtr _instrcontinue();
  ASTInstrExprPtr _instrexpr();
  ASTInstrIfPtr _instrif();
  ASTInstrReturnPtr _instrreturn();
  ASTInstrVarPtr _instrvar();
  ASTInstrWhilePtr _instrwhile();

  ASTTypeIdPtr _typeid();

  ASTExprPtr _expr();

  ASTExprPtr _expr_ops00(); // () [] .
  ASTExprPtr _expr_ops01(); //* & - ! ~ (RTL unary ops)
  ASTExprPtr _expr_ops02(); // * / %
  ASTExprPtr _expr_ops03(); // + -
  ASTExprPtr _expr_ops04(); // >> <<
  ASTExprPtr _expr_ops05(); // < > <= >=
  ASTExprPtr _expr_ops06(); // == !=
  ASTExprPtr _expr_ops07(); // &
  ASTExprPtr _expr_ops08(); // ^
  ASTExprPtr _expr_ops09(); // |
  ASTExprPtr _expr_ops10(); // &&
  ASTExprPtr _expr_ops11(); // ||
  ASTExprPtr _expr_ops12(); // = (RTL assign ops)

  ASTExprPtr _expr0(); // '(' expr ')' | expr_symbol | sizeof | explit cast
  ASTExprPtr _expr_symbol();          // float, int, string, id
  ast_exprs_list_t _expr_call_list(); // expr list (separated by ',')
};

} // namespace cgen
