#include "parser/parser.hh"

#include "ast/all.hh"
#include "parser/lexer.hh"

#include "obcl/parser/parser-error.hh"

#include <cassert>

using obcl::Token;

namespace milk {

Parser::Parser() : obcl::Parser(token_infos_custom), _ast(nullptr) {}

void Parser::parse_file(const std::string &path) {
  assert(!_ast.get());
  _lex.set_stream_file(path);
  _ast = _r_file();
}

void Parser::parse_string(const std::string &str) {
  assert(!_ast.get());
  _lex.set_stream_raw(str);
  _ast = _r_file();
}

// file: def+ @eof
ASTProgramPtr Parser::_r_file() {
  std::vector<ASTDefPtr> defs;
  while (_peek_any_of({TOK_KW_FN, TOK_KW_TYPE, TOK_KW_STRUCT, TOK_KW_ENUM}))
    defs.emplace_back(_r_def());
  _consume_of_type(obcl::TOK_EOF, "r:file");
  return std::make_unique<ASTProgram>(std::move(defs));
}

// def:   fundef
//     |  aliasef
//     |  structdef
//     |  enumdef
ASTDefPtr Parser::_r_def() {
  auto tok = _peek_token();
  switch (tok.type) {
  case TOK_KW_FN:
    return _r_fundef();
  case TOK_KW_TYPE:
    return _r_aliasdef();
  case TOK_KW_STRUCT:
    return _r_structdef();
  case TOK_KW_ENUM:
    return _r_enumdef();
  default:
    throw obcl::ParserError(tok.loc, "r:def invalid token");
  }
}

// fundef: 'fn' @id '(' <fundef_argslist> ')' ':' <typelabel> <stmt>
ASTDefFunPtr Parser::_r_fundef() {
  auto beg_tok = _consume_of_type(TOK_KW_FN, "r:fundef: expected keyword 'fn'");
  auto name = _consume_id("r:fundef: expected function name");
  _consume_of_type(TOK_SYM_LRBRAC, "r:fundef: expected '('");
  auto args = _r_fundef_argslist();
  _consume_of_type(TOK_SYM_RRBRAC, "r:fundef: expected ')'");
  _consume_of_type(TOK_SYM_COLON, "r:fundef: expected ':'");
  auto ret_type = _r_typelabel();
  auto body = _r_stmt();
  return std::make_unique<ASTDefFun>(beg_tok.loc, ASTDefFun::Kind::FUN, name,
                                     std::move(args), std::move(ret_type),
                                     std::move(body));
}

// fundef_argslist:  <fundef_arg> (',' <fundef_arg>)*
//		     | ((empty))
//
// fundef_arg: ['const'] @id ':' <typelabel>
ast_storage_list_t Parser::_r_fundef_argslist() {
  ast_storage_list_t res;
  bool has_coma = false;

  while (true) {
    if (!has_coma)
      _consume_of_type(TOK_SYM_RRBRAC,
                       "r_fundef_argslist: expected end of arguments ')'");

    auto beg_tok = obcl::Token::eof();
    bool is_const = _consume_if_type(TOK_KW_CONST, &beg_tok);
    auto name = _consume_of_type(obcl::TOK_ID,
                                 "r:fundef_argslist: exepected argument name");
    if (!is_const)
      beg_tok = name;
    _consume_of_type(TOK_SYM_COLON, "r:fundef_argslist: expected ':'");
    auto type = _r_typelabel();
    auto end_loc = type->loc();
    res.push_back(
        std::make_unique<ASTNamedStorage>(obcl::Location(beg_tok.loc, end_loc),
                                          name.val, is_const, std::move(type)));

    has_coma = _consume_if_type(TOK_SYM_COMA);
  }

  return res;
}

// aliasdef: 'type' @id '=' <typelabel> ';'
ASTDefAliasPtr Parser::_r_aliasdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_TYPE, "r_aliasdef: expected keyword 'type'");
  auto name = _consume_id("r_aliasdef: expected type alias name");
  _consume_of_type(TOK_SYM_EQ,
                   "r_aliasdef: expected symbol '=' after alias name");
  auto type = _r_typelabel();
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r_aliasdef: expected symbol ';' at the end of an alias definition");
  return std::make_unique<ASTDefAlias>(beg_tok.loc, end_tok.loc, name,
                                       std::move(type));
}

// structdef: 'struct' @id '{' <structdef_field>+ '}' ';'
ASTDefStructPtr Parser::_r_structdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_STRUCT, "r:structdef: expected keyword 'struct'");
  auto name = _consume_id("r:structdef: expected struct name");
  _consume_of_type(TOK_SYM_LCBRAC, "r:structdef: expected symbol '{'");

  ast_defs_list_t fields;
  while (!_consume_if_type(TOK_SYM_RCBRAC))
    fields.push_back(_r_structdef_field());

  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:structdef: expected symbol ';' at the end of a struct definition");
  return std::make_unique<ASTDefStruct>(beg_tok.loc, end_tok.loc, name,
                                        std::move(fields));
}

// structdef_field:   structdef_attr
//		     |  structdef_meth
ASTDefPtr Parser::_r_structdef_field() {
  auto tok = _peek_token();
  switch (tok.type) {
  case TOK_KW_LET:
  case TOK_KW_CONST:
    return _r_structdef_attr();
  case TOK_KW_FN:
    return _r_structdef_meth();
  default:
    throw obcl::ParserError(tok.loc, "r:structdef_field: invalid token");
  };
}

// structdef_attr:   'let'|'const' @id ':' <typelabel> ';'
ASTDefVarPtr Parser::_r_structdef_attr() {
  auto beg_tok =
      _consume_of_type({TOK_KW_LET, TOK_KW_CONST},
                       "r:structdef_attr: expected keyword 'let' or 'const'");
  bool is_const = beg_tok.type == TOK_KW_CONST;
  auto name = _consume_id("r:structdef_atrr: expected attr name");
  _consume_of_type(TOK_SYM_COLON, "r:structdef_attr: expected symbol ':'");
  auto type = _r_typelabel();
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:struct_attr: expected ';' at the end of struct attr definition");

  obcl::Location loc(beg_tok.loc, end_tok.loc);
  return std::make_unique<ASTDefVar>(
      loc, ASTDefVar::Kind::STRUCT_FIELD,
      std::make_unique<ASTNamedStorage>(loc, name, is_const, std::move(type)));
}

// structdef_meth: 'fn' @id '(' <fundef_argslist> ')' ['const'] ':'
// <typelabel> <stmt>
ASTDefFunPtr Parser::_r_structdef_meth() {
  auto beg_tok =
      _consume_of_type(TOK_KW_FN, "r:structdef_meth: expected keyword 'fn'");
  auto name = _consume_id("r:structdef_meth: expected method name");
  _consume_of_type(TOK_SYM_LRBRAC, "r:structdef_meth: expected '('");
  auto args = _r_fundef_argslist();
  _consume_of_type(TOK_SYM_RRBRAC, "r:structdef_meth: expected ')'");
  _consume_of_type(TOK_SYM_COLON, "r:structdef_meth: expected ':'");
  bool is_const = _consume_if_type(TOK_KW_CONST);
  auto ret_type = _r_typelabel();
  auto body = _r_stmt();
  return std::make_unique<ASTDefFun>(
      beg_tok.loc,
      is_const ? ASTDefFun::Kind::METH_CONST : ASTDefFun::Kind::METH, name,
      std::move(args), std::move(ret_type), std::move(body));
}

// enumdef: 'enum' @id [':' <typelabel>] '{' <enumdef_field>+ '}' ';'
//
// enumdef_field: @id ['=' @int] ';'
ASTDefEnumPtr Parser::_r_enumdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_ENUM, "r:enumdef: expected keyword 'enum'");
  auto name = _consume_id("r:enumdef: expected enum name");
  auto type = _consume_if_type(TOK_SYM_COLON)
                  ? _r_typelabel()
                  : std::make_unique<ASTTypeLabelName>(
                        beg_tok.loc, ASTDefEnum::DEF_TYPENAME);

  _consume_of_type(TOK_SYM_LCBRAC, "r:enumdef: expected symbol '{'");
  ASTDefEnum::fields_t fields;
  int next_val = 0;
  while (_peek_type() == obcl::TOK_ID) {
    auto name = _consume_id("r:enumdef: expected enum field name");
    int val =
        _consume_if_type(TOK_SYM_EQ)
            ? _consume_cint("r:enumdef: expected int for enum field value")
            : next_val;
    _consume_of_type(
        TOK_SYM_SEMI,
        "r:enumdef: expected symbol ';' at the end of an enum field");
    next_val = val + 1;
    fields.emplace_back(name, val);
  }

  _consume_of_type(TOK_SYM_RCBRAC, "r:enumdef: expected symbol '}'");
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:enumdef: expected symbol ';' at the end of enum definition");
  return std::make_unique<ASTDefEnum>(beg_tok.loc, end_tok.loc, name,
                                      std::move(type), fields);
}

// typelabel:   <valuetypelabel>
//	       | '&' <valuetypelabel>
//	       | '&const' <valuetypelabel>
//	       | '&[]' <valuetypelabel>
//	       | '&[]const' <valuetypelabel>
//
// valuetypelabel: @id
ASTTypeLabelPtr Parser::_r_typelabel() {

  auto beg_tok = _get_token();
  switch (beg_tok.type) {

  case obcl::TOK_ID:
    return std::make_unique<ASTTypeLabelName>(beg_tok);

  case TOK_SYM_MREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::MUT_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&'")));

  case TOK_SYM_CREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::CONST_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&const'")));

  case TOK_SYM_MAREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::MUT_ARR_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&[]'")));

  case TOK_SYM_CAREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::CONST_ARR_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&[]const'")));

  default:
    throw obcl::ParserError(beg_tok.loc, "r:typelabel invalid token");
  }
}

// stmt:
//	     stmt_block
//	   | stmt_expr
//	   | stmt_vardef
//	   | stmt_if
//	   | stmt_while
//	   | stmt_break
//	   | stmt_continue
//	   | stmt_return
ASTStmtPtr Parser::_r_stmt() {
  switch (_peek_type()) {
  case TOK_SYM_LCBRAC:
    return _r_stmt_block();
  case TOK_KW_LET:
  case TOK_KW_CONST:
    return _r_stmt_vardef();
  case TOK_KW_IF:
    return _r_stmt_if();
  case TOK_KW_WHILE:
    return _r_stmt_while();
  case TOK_KW_BREAK:
    return _r_stmt_break();
  case TOK_KW_CONTINUE:
    return _r_stmt_continue();
  case TOK_KW_RETURN:
    return _r_stmt_return();
  default:
    return _r_stmt_expr();
  }
}

// stmt_block: '{' <stmt>* '}'
ASTStmtBlockPtr Parser::_r_stmt_block() {
  auto beg_tok =
      _consume_of_type(TOK_SYM_LCBRAC, "r:stmt_block: expected symbol '{'");
  ast_stmts_list_t res;
  auto end_tok = obcl::Token::eof();
  while (!_consume_if_type(TOK_SYM_RCBRAC, &end_tok))
    res.push_back(_r_stmt());
  return std::make_unique<ASTStmtBlock>(beg_tok.loc, end_tok.loc,
                                        std::move(res));
}

// stmt_expr: <expr> ';'
ASTStmtExprPtr Parser::_r_stmt_expr() {
  auto expr = _r_expr();
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:stmt_expr: expression statement must be terminated by symbol ';'");
  return std::make_unique<ASTStmtExpr>(end_tok.loc, std::move(expr));
}

// stmt_vardef:   'let'|'const' @id [':' <typelabel>] '=' <expr> ';'
ASTStmtVarPtr Parser::_r_stmt_vardef() {
  auto beg_tok =
      _consume_of_type({TOK_KW_LET, TOK_KW_CONST},
                       "r:stmt_vardef: expected keyword 'let' or 'const'");
  bool is_const = beg_tok.type == TOK_KW_CONST;
  auto name = _consume_id("r:stmt_vardef: expected variable name");

  ASTTypeLabelPtr type = nullptr;
  if (_consume_if_type(TOK_SYM_COLON))
    type = _r_typelabel();

  _consume_of_type(TOK_SYM_EQ, "r:stmt_vardef: expected symbol '='");
  auto init = _r_expr();
  auto end_tok = _consume_of_type(TOK_SYM_SEMI,
                                  "r:stmt_vardef: variable definition "
                                  "statement must be terminated by symbol ';'");

  obcl::Location loc(beg_tok.loc, end_tok.loc);
  return std::make_unique<ASTStmtVar>(
      beg_tok.loc, end_tok.loc,
      std::make_unique<ASTNamedStorage>(loc, name, is_const, std::move(type)),
      std::move(init));
}

// stmt_if: 'if' '(' <expr> ')' <stmt> ['else' <stmt>]
// !ambiguity! else always connected to the closest if
ASTStmtIfPtr Parser::_r_stmt_if() {
  auto beg_tok =
      _consume_of_type(TOK_KW_IF, "r:stmt_if: expected keyword 'if'");
  _consume_of_type(TOK_SYM_LRBRAC,
                   "r:stmt_if: expected symbol '(' around condition");
  auto cond = _r_expr();
  _consume_of_type(TOK_SYM_RRBRAC,
                   "r:stmt_if: expected symbol ')' around condition");
  auto if_stmt = _r_stmt();

  auto else_stmt =
      _consume_if_type(TOK_KW_ELSE)
          ? _r_stmt()
          : std::make_unique<ASTStmtBlock>(if_stmt->loc(), if_stmt->loc(),
                                           ast_stmts_list_t{});

  return std::make_unique<ASTStmtIf>(beg_tok.loc, std::move(cond),
                                     std::move(if_stmt), std::move(else_stmt));
}

// stmt_while: 'while' '(' <expr> ')' <stmt>
ASTStmtWhilePtr Parser::_r_stmt_while() {
  auto beg_tok =
      _consume_of_type(TOK_KW_WHILE, "r:stmt_while: expected keyword 'while'");
  _consume_of_type(TOK_SYM_LRBRAC,
                   "r:stmt_while: expected symbol '(' around condition");
  auto cond = _r_expr();
  _consume_of_type(TOK_SYM_RRBRAC,
                   "r:stmt_while: expected symbol ')' around condition");
  auto body = _r_stmt();
  return std::make_unique<ASTStmtWhile>(beg_tok.loc, std::move(cond),
                                        std::move(body));
}

// stmt_break: 'break' ';'
ASTStmtBreakPtr Parser::_r_stmt_break() {
  auto beg_tok =
      _consume_of_type(TOK_KW_BREAK, "r:stmt_break: expected keyword 'break'");
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:stmt_break: expected symbol ';' at the end of a break statement");
  return std::make_unique<ASTStmtBreak>(beg_tok.loc, end_tok.loc,
                                        ASTStmtBreak::Kind::BREAK);
}

// stmt_break: 'continue' ';'
ASTStmtBreakPtr Parser::_r_stmt_continue() {
  auto beg_tok = _consume_of_type(
      TOK_KW_CONTINUE, "r:stmt_continue: expected keyword 'continue'");
  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "r:stmt_continue: expected symbol ';' at "
                                     "the end of a continue statement");
  return std::make_unique<ASTStmtBreak>(beg_tok.loc, end_tok.loc,
                                        ASTStmtBreak::Kind::CONTINUE);
}

// stmt_return: 'return' [expr>] ';'
ASTStmtReturnPtr Parser::_r_stmt_return() {
  auto beg_tok = _consume_of_type(TOK_KW_RETURN,
                                  "r:stmt_return: expected keyword 'return'");
  auto val = _peek_type() == TOK_SYM_SEMI ? nullptr : _r_expr();
  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "r:stmt_return: expected symbol ';' at "
                                     "the end of a return statement");
  return std::make_unique<ASTStmtReturn>(beg_tok.loc, end_tok.loc,
                                         std::move(val));
}

ASTExprPtr Parser::_r_expr() { return _r_expr_12(); }

// expr_12:  expr11
//	     | expr_11 ('=' | '*=' | '/=' | '%=' | '+=' | '-=') expr_12
ASTExprPtr Parser::_r_expr_12() {
  auto left = _r_expr_11();
  const char *fn = nullptr;

  switch (_peek_type()) {
  case TOK_SYM_EQ:
    fn = ASTExprCall::OP_SET;
    break;
  case TOK_SYM_ADD_EQ:
    fn = ASTExprCall::OP_SETADD;
    break;
  case TOK_SYM_SUB_EQ:
    fn = ASTExprCall::OP_SETSUB;
    break;
  case TOK_SYM_MUL_EQ:
    fn = ASTExprCall::OP_SETMUL;
    break;
  case TOK_SYM_DIV_EQ:
    fn = ASTExprCall::OP_SETDIV;
    break;
  case TOK_SYM_MOD_EQ:
    fn = ASTExprCall::OP_SETMOD;
    break;
  default:
    return left;
  }

  auto right = _r_expr_12();
  obcl::Location loc(left->loc(), right->loc());
  auto callee = std::make_unique<ASTExprId>(loc, fn);
  ast_exprs_list_t args;
  args.push_back(std::move(left));
  args.push_back(std::move(right));
  return std::make_unique<ASTExprCall>(loc, std::move(callee), std::move(args));
}

// expr_11:  expr_10
//	     | expr_10 '?' expr_11 ':' expr_11
ASTExprPtr Parser::_r_expr_11() {
  auto left = _r_expr_10();
  if (!_consume_if_type(TOK_SYM_QUESTION))
    return left;

  auto if_val = _r_expr_10();
  _consume_of_type(
      TOK_SYM_COLON,
      "r:expr: expected ':' after second operand of ternary operator");
  auto else_val = _r_expr_11();

  obcl::Location loc(left->loc(), else_val->loc());
  ast_exprs_list_t args;
  args.push_back(std::move(left));
  args.push_back(std::move(if_val));
  args.push_back(std::move(else_val));
  return std::make_unique<ASTExprSpecial>(loc, ASTExprSpecial::Kind::OP_TERNARY,
                                          std::move(args));
}

} // namespace milk
