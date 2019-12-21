//===--parser/parser.hh - Parser class definition ---------------*- C++ -*-===//
//
// milk compiler library
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
#include <string>

namespace milk {

/// Parser for milk language
/// Read a single source file or raw code string
/// Build an AST
class Parser : public obcl::Parser {

public:
  Parser();

  /// Parse file and build the AST
  /// (can create only one AST)
  void parse_file(const std::string &path);

  /// Parse string of code and build the AST
  /// (can create only one AST)
  void parse_string(const std::string &str);

  const ASTProgram &ast() const { return *_ast; }

private:
  ASTProgramPtr _ast;

  // AST creation methods

  // file: def+ @eof
  ASTProgramPtr _r_file();

  // def:   fundef
  //     |  aliasef
  //     |  structdef
  //     |  enumdef
  ASTDefPtr _r_def();

  // fundef: 'fn' @id '(' <fundef_argslist> ')' ':' <typelabel> <stmt>
  //
  // fundef_argslist:  <fundef_arg> (',' <fundef_arg>)*
  //		     | ((empty))
  //
  // fundef_arg: ['const'] @id ':' <typelabel>
  ASTDefFunPtr _r_fundef();

  // aliasdef: 'type' @id '=' <typelabel> ';'
  ASTDefAliasPtr _r_aliasdef();

  // structdef: 'struct' @id '{' <structdef_field>+ '}' ';'
  ASTDefStructPtr _r_structdef();

  // structdef_field:   structdef_attr
  //		     |  structdef_meth
  ASTDefPtr _r_structdef_field();

  // structdef_attr:   'let'|'const' @id ':' <typelabel> ';'
  ASTDefVarPtr _r_structdef_attr();

  // structdef_meth: 'fn' @id '(' <fundef_argslist> ')' ['const'] ':'
  // <typelabel> <stmt>
  ASTDefFunPtr _r_structdef_meth();

  // enumdef: 'enum' @id [':' <typelabel>] '{' <enumdef_field>+ '}' ';'
  //
  // enumdef_field: @id ['=' @int] ';'
  ASTDefEnumPtr _r_enumdef();

  // typelabel:   <valuetypelabel>
  //	       | '&' <valuetypelabel>
  //	       | '&const' <valuetypelabel>
  //	       | '&[]' <valuetypelabel>
  //	       | '&[]const' <valuetypelabel>
  //
  // valuetypelabel: @id
  ASTTypeLabelPtr _r_typelbale();

  // stmt:
  //	     stmt_block
  //	   | stmt_expr
  //	   | stmt_vardef
  //	   | stmt_if
  //	   | stmt_while
  //	   | stmt_break
  //	   | stmt_continue
  //	   | stmt_return
  ASTStmtPtr _r_stmt();

  // stmt_block: '{' <stmt>* '}'
  ASTStmtBlockPtr _r_stmt_block();

  // stmt_expr: <expr> ';'
  ASTStmtExprPtr _r_stmt_expr();

  // stmt_vardef:   'let'|'const' @id [':' <typelabel>] '=' <expr> ';'
  ASTStmtVarPtr _r_stmt_vardef();

  // stmt_if: 'if' '(' <expr> ')' <stmt> ['else' <stmt>]
  // !ambiguity! else always connected to the closest if
  ASTStmtIfPtr _r_stmt_if();

  // stmt_while: 'while' '(' <expr> ')' <stmt>
  ASTStmtWhilePtr _r_stmt_while();

  // stmt_break: 'break' ';'
  ASTStmtBreakPtr _r_stmt_break();

  // stmt_break: 'continue' ';'
  ASTStmtBreakPtr _r_stmt_continue();

  // stmt_return: 'return' [expr>] ';'
  ASTStmtReturnPtr _r_stmt_return();

  // expr: expr_12
  ASTStmtExpr _r_expr();
};

} // namespace milk
