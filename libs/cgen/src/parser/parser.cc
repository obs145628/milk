#include "parser/parser.hh"
#include "ast/all.hh"
#include "obcl/parser/parser-error.hh"
#include "parser/lexer.hh"

#include <iostream>

using obcl::Token;

namespace cgen {

Parser::Parser()
    : obcl::Parser(token_infos_custom),
      _main_ast(std::make_unique<ASTProgram>()) {}

void Parser::parse_file(const std::string &path) {
  _lex.set_stream_file(path);
  _main_ast->extend(_program());
}

// parse one raw string
void Parser::parse_string(const std::string &str) {
  _lex.set_stream_raw(str);
  _main_ast->extend(_program());
}

ASTProgramPtr Parser::_program() {
  std::vector<ASTDefPtr> defs;
  while (true) {
    Token tok = _peek_token();
    if (tok.type != TOK_KW_FN && tok.type != TOK_KW_STRUCT &&
        tok.type != TOK_KW_TYPE && tok.type != TOK_KW_VAR)
      break;

    defs.emplace_back(_def());
  }

  _consume_of_type(obcl::TOK_EOF, "parse_program");

  return std::make_unique<ASTProgram>(std::move(defs));
}

ASTDefPtr Parser::_def() {
  Token tok = _peek_token();
  if (tok.type == TOK_KW_FN)
    return _fundef();
  else if (tok.type == TOK_KW_STRUCT)
    return _structdef();
  else if (tok.type == TOK_KW_TYPE)
    return _typedef();
  else if (tok.type == TOK_KW_VAR)
    return _vardef();

  else
    throw obcl::ParserError(tok.loc, "parse_def: invalid token");
}

ASTDefFunPtr Parser::_fundef() {
  auto beg_tok = _consume_of_type(TOK_KW_FN, "parse_fundef: expected 'fn'");
  auto ret_type = _typeid();
  auto name = _consume_id("parse_fundef: expected function name");
  _consume_of_type(TOK_SYM_LPAREN, "parse_fundef: expected '('");
  auto args = _fieldsdef();
  _consume_of_type(TOK_SYM_RPAREN, "parse_fundef: expected ')'");

  ASTInstrPtr body = nullptr;
  auto tok = _peek_token();
  obcl::Location end_loc = tok.loc;

  if (tok.type == TOK_SYM_SEMI) {
    _get_token();
  } else {
    body = _instr();
    end_loc = body->loc();
  }

  return std::make_unique<ASTDefFun>(beg_tok.loc, end_loc, name,
                                     std::move(ret_type), std::move(args),
                                     std::move(body));
}

ASTDefStructPtr Parser::_structdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_STRUCT, "parse_structdef: expected 'struct'");
  auto name = _consume_id("parse_structdef: expected struct name");
  _consume_of_type(TOK_SYM_LCBRACK, "parse_structdef: expected '{'");
  auto fields = _fieldsdef();
  _consume_of_type(TOK_SYM_RCBRACK, "parse_structdef: expected '}'");
  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "parse_structdef: expected ';'");
  return std::make_unique<ASTDefStruct>(beg_tok.loc, end_tok.loc, name,
                                        std::move(fields));
}

ASTDefTypePtr Parser::_typedef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_TYPE, "parse_typedef: expected 'type'");
  auto name = _consume_id("parse_typedef: expected type alias name");
  _consume_of_type(TOK_SYM_EQ, "parse_typedef: expected '='");
  auto type = _typeid();
  auto end_tok = _consume_of_type(TOK_SYM_SEMI, "parse_typedef: expected ';'");
  return std::make_unique<ASTDefType>(beg_tok.loc, end_tok.loc, name,
                                      std::move(type));
}

ASTDefVarPtr Parser::_vardef() {
  auto beg_tok = _consume_of_type(TOK_KW_VAR, "parse_vardef: expected 'var'");
  auto type = _typeid();
  auto name = _consume_id("parse_vardef: expected variable name");

  ASTExprPtr val = nullptr;
  if (_consume_if_type(TOK_SYM_EQ))
    val = _expr();

  auto end_tok = _consume_of_type(TOK_SYM_SEMI, "parse_vardef: expected ':'");
  return std::make_unique<ASTDefVar>(beg_tok.loc, end_tok.loc, name,
                                     std::move(type), std::move(val));
}

ast_args_def_t Parser::_fieldsdef() {
  ast_args_def_t fields;
  bool missing_comma = false;

  while (true) {

    Token tok = _peek_token();
    if (tok.type != obcl::TOK_ID)
      break;

    if (missing_comma)
      throw obcl::ParserError(tok.loc, "parse_fieldsdef: expected ','");
    missing_comma = true;

    auto name = _get_token().val;
    _consume_of_type(TOK_SYM_COLON, "parse_fieldsdef: expected ':'");
    auto type = _typeid();
    fields.emplace_back(std::move(type), name);

    if (_consume_if_type(TOK_SYM_COMMA))
      missing_comma = false;
  }

  return fields;
}

ASTInstrPtr Parser::_instr() {
  Token tok = _peek_token();
  if (tok.type == TOK_SYM_LCBRACK)
    return _instrblock();
  else if (tok.type == TOK_KW_BREAK)
    return _instrbreak();
  else if (tok.type == TOK_KW_CONTINUE)
    return _instrcontinue();
  else if (tok.type == TOK_KW_IF)
    return _instrif();
  else if (tok.type == TOK_KW_RETURN)
    return _instrreturn();
  else if (tok.type == TOK_KW_VAR)
    return _instrvar();
  else if (tok.type == TOK_KW_WHILE)
    return _instrwhile();

  return _instrexpr();
}

ASTInstrBlockPtr Parser::_instrblock() {
  auto beg_tok =
      _consume_of_type(TOK_SYM_LCBRACK, "parse_instrblock: expected '{'");
  std::vector<ASTInstrPtr> res;

  while (true) {
    if (_peek_type() == TOK_SYM_RCBRACK)
      break;
    res.push_back(_instr());
  }

  auto end_tok =
      _consume_of_type(TOK_SYM_RCBRACK, "parse_instrblock: expected '}'");
  return std::make_unique<ASTInstrBlock>(beg_tok.loc, end_tok.loc,
                                         std::move(res));
}

ASTInstrBreakPtr Parser::_instrbreak() {
  auto beg_tok =
      _consume_of_type(TOK_KW_BREAK, "parse_instrbreak: expected 'break'");
  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "parse_instrbreak: expected ';'");
  return std::make_unique<ASTInstrBreak>(beg_tok.loc, end_tok.loc);
}

ASTInstrContinuePtr Parser::_instrcontinue() {
  auto beg_tok = _consume_of_type(TOK_KW_CONTINUE,
                                  "parse_instrcontinue: expected 'continue'");
  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "parse_instrcontinue: expected ';'");
  return std::make_unique<ASTInstrContinue>(beg_tok.loc, end_tok.loc);
}

ASTInstrExprPtr Parser::_instrexpr() {
  auto val = _expr();
  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "parse_instrexpr: expected ';'");
  return std::make_unique<ASTInstrExpr>(end_tok.loc, std::move(val));
}

ASTInstrIfPtr Parser::_instrif() {
  auto beg_tok = _consume_of_type(TOK_KW_IF, "parse_instrif: expected 'if'");
  _consume_of_type(TOK_SYM_LPAREN, "parse_instrif: expected '('");
  auto cond = _expr();
  _consume_of_type(TOK_SYM_RPAREN, "parse_instrif: expected ')'");

  auto if_ins = _instr();

  ASTInstrPtr else_ins;
  if (_consume_if_type(TOK_KW_ELSE))
    else_ins = _instr();
  else
    else_ins = ASTInstrBlock::empty(if_ins->loc());

  return std::make_unique<ASTInstrIf>(beg_tok.loc, std::move(cond),
                                      std::move(if_ins), std::move(else_ins));
}

ASTInstrReturnPtr Parser::_instrreturn() {
  auto beg_tok =
      _consume_of_type(TOK_KW_RETURN, "parse_instrreturn: expected 'return'");

  ASTExprPtr val = nullptr;
  if (_peek_type() != TOK_SYM_SEMI)
    val = _expr();

  auto end_tok =
      _consume_of_type(TOK_SYM_SEMI, "parse_instrreturn: expected ';'");
  return std::make_unique<ASTInstrReturn>(beg_tok.loc, end_tok.loc,
                                          std::move(val));
}

ASTInstrVarPtr Parser::_instrvar() {
  auto beg_tok = _consume_of_type(TOK_KW_VAR, "parse_instrvar: expected 'var'");
  auto type = _typeid();
  auto name = _consume_id("parse_instrvar: expected variable name");
  auto end_tok = _consume_of_type(TOK_SYM_SEMI, "parse_instrvar: expected ';'");
  return std::make_unique<ASTInstrVar>(beg_tok.loc, end_tok.loc, name,
                                       std::move(type));
}

ASTInstrWhilePtr Parser::_instrwhile() {
  auto beg_tok =
      _consume_of_type(TOK_KW_WHILE, "parse_instrwhile: expected 'while'");
  _consume_of_type(TOK_SYM_LPAREN, "parse_instrwhile: expected '('");
  auto cond = _expr();
  _consume_of_type(TOK_SYM_RPAREN, "parse_instrwhile: expected ')'");
  auto body = _instr();
  return std::make_unique<ASTInstrWhile>(beg_tok.loc, std::move(cond),
                                         std::move(body));
}

ASTTypeIdPtr Parser::_typeid() {
  auto name = _consume_of_type(obcl::TOK_ID, "parse_typeid: expected typename");
  ASTTypeIdPtr res = std::make_unique<ASTTypeIdName>(name);

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_MUL)
      break;
    _get_token();
    res = std::make_unique<ASTTypeIdPointer>(tok.loc, std::move(res));
  }

  return res;
}

ASTExprPtr Parser::_expr() { return _expr_ops12(); }

ASTExprPtr Parser::_expr_ops00() // () [] .
{
  auto left = _expr0();
  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_SYM_LPAREN && tok.type != TOK_SYM_DOT)
      break;

    if (tok.type == TOK_SYM_LPAREN) {
      _get_token();
      auto args = _expr_call_list();
      auto end_tok =
          _consume_of_type(TOK_SYM_RPAREN, "parse_expr: expected ')'");
      left = std::make_unique<ASTExprCall>(end_tok.loc, std::move(left),
                                           std::move(args));
    }

    else {
      _get_token();
      auto field =
          _consume_of_type(obcl::TOK_ID, "parse_expr: expected field name");
      left = std::make_unique<ASTExprField>(std::move(left), field);
    }
  }

  return left;
}

ASTExprPtr Parser::_expr_ops01() //* & - ! ~ (RTL unary ops)
{
  auto tok = _peek_token();
  if (tok.type != TOK_OP_MUL && tok.type != TOK_OP_BAND &&
      tok.type != TOK_OP_SUB && tok.type != TOK_OP_NOT &&
      tok.type != TOK_OP_BNOT)
    return _expr_ops00();
  _get_token();

  auto val = _expr_ops01();
  if (tok.type == TOK_OP_MUL)
    return std::make_unique<ASTExprUnOp>(tok.loc, ASTExprUnOp::Op::DEREF,
                                         std::move(val));
  else if (tok.type == TOK_OP_BAND)
    return std::make_unique<ASTExprUnOp>(tok.loc, ASTExprUnOp::Op::ADDR,
                                         std::move(val));
  else if (tok.type == TOK_OP_SUB)
    return std::make_unique<ASTExprUnOp>(tok.loc, ASTExprUnOp::Op::NEG,
                                         std::move(val));
  else if (tok.type == TOK_OP_NOT)
    return std::make_unique<ASTExprUnOp>(tok.loc, ASTExprUnOp::Op::NOT,
                                         std::move(val));
  else
    return std::make_unique<ASTExprUnOp>(tok.loc, ASTExprUnOp::Op::BNOT,
                                         std::move(val));
}

ASTExprPtr Parser::_expr_ops02() // * / %
{
  auto left = _expr_ops01();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_MUL && tok.type != TOK_OP_DIV &&
        tok.type != TOK_OP_MOD)
      break;
    _get_token();

    auto right = _expr_ops01();

    if (tok.type == TOK_OP_MUL)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::MUL,
                                            std::move(left), std::move(right));
    else if (tok.type == TOK_OP_DIV)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::DIV,
                                            std::move(left), std::move(right));
    else
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::MOD,
                                            std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops03() // + -
{
  auto left = _expr_ops02();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_ADD && tok.type != TOK_OP_SUB)
      break;
    _get_token();

    auto right = _expr_ops02();

    if (tok.type == TOK_OP_ADD)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::ADD,
                                            std::move(left), std::move(right));
    else
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::SUB,
                                            std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops04() // >> <<
{
  auto left = _expr_ops03();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_BLS && tok.type != TOK_OP_BRS)
      break;
    _get_token();

    auto right = _expr_ops03();

    if (tok.type == TOK_OP_BLS)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::BLS,
                                            std::move(left), std::move(right));
    else
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::BRS,
                                            std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops05() // < > <= >=
{
  auto left = _expr_ops04();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_GT && tok.type != TOK_OP_LT &&
        tok.type != TOK_OP_GE && tok.type != TOK_OP_LE)
      break;
    _get_token();

    auto right = _expr_ops04();

    if (tok.type == TOK_OP_GT)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::GT,
                                            std::move(left), std::move(right));
    else if (tok.type == TOK_OP_LT)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::LT,
                                            std::move(left), std::move(right));
    else if (tok.type == TOK_OP_GE)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::GEQ,
                                            std::move(left), std::move(right));
    else
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::LEQ,
                                            std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops06() // == !=
{
  auto left = _expr_ops05();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_EQ && tok.type != TOK_OP_NE)
      break;
    _get_token();

    auto right = _expr_ops05();

    if (tok.type == TOK_OP_EQ)
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::EQ,
                                            std::move(left), std::move(right));
    else
      left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::NEQ,
                                            std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops07() // &
{
  auto left = _expr_ops06();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_BAND)
      break;
    _get_token();

    auto right = _expr_ops06();
    left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::BAND,
                                          std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops08() {
  auto left = _expr_ops07();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_BXOR)
      break;
    _get_token();

    auto right = _expr_ops07();
    left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::BXOR,
                                          std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops09() // |
{
  auto left = _expr_ops08();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_BOR)
      break;
    _get_token();

    auto right = _expr_ops08();
    left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::BOR,
                                          std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops10() // &&
{
  auto left = _expr_ops09();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_AND)
      break;
    _get_token();

    auto right = _expr_ops09();
    left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::AND,
                                          std::move(left), std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops11() // ||
{
  auto left = _expr_ops10();

  while (true) {
    auto tok = _peek_token();
    if (tok.type != TOK_OP_OR)
      break;
    _get_token();

    auto right = _expr_ops10();
    left = std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::OR, std::move(left),
                                          std::move(right));
  }

  return left;
}

ASTExprPtr Parser::_expr_ops12() // = (RTL assign ops)
{
  auto left = _expr_ops11();
  auto tok = _peek_token();
  if (tok.type != TOK_SYM_EQ)
    return left;

  _get_token();
  auto right = _expr_ops12();
  return std::make_unique<ASTExprBinOp>(ASTExprBinOp::Op::ASSIGN,
                                        std::move(left), std::move(right));
}

ASTExprPtr Parser::_expr0() // sizeof, casts, (<expr>)
{
  auto tok = _peek_token();

  if (tok.type == TOK_KW_SIZEOF) {
    _get_token();
    auto type = _typeid();
    return std::make_unique<ASTExprSizeof>(tok.loc, std::move(type));
  }

  else if (tok.type == TOK_KW_STATIC_CAST) {
    _get_token();
    auto type = _typeid();
    _consume_of_type(TOK_SYM_LPAREN, "parse_expr: expected '('");
    auto val = _expr();
    auto end_tok = _consume_of_type(TOK_SYM_RPAREN, "parse_expr: expected ')'");
    return std::make_unique<ASTExprCast>(tok.loc, end_tok.loc,
                                         ASTExprCast::Kind::STATIC,
                                         std::move(type), std::move(val));
  }

  else if (tok.type == TOK_KW_PTR_CAST) {
    _get_token();
    auto type = _typeid();
    _consume_of_type(TOK_SYM_LPAREN, "parse_expr: expected '('");
    auto val = _expr();
    auto end_tok = _consume_of_type(TOK_SYM_RPAREN, "parse_expr: expected ')'");
    return std::make_unique<ASTExprCast>(tok.loc, end_tok.loc,
                                         ASTExprCast::Kind::PTR,
                                         std::move(type), std::move(val));
  }

  else if (tok.type == TOK_KW_REINTERPRET_CAST) {
    _get_token();
    auto type = _typeid();
    _consume_of_type(TOK_SYM_LPAREN, "parse_expr: expected '('");
    auto val = _expr();
    auto end_tok = _consume_of_type(TOK_SYM_RPAREN, "parse_expr: expected ')'");
    return std::make_unique<ASTExprCast>(tok.loc, end_tok.loc,
                                         ASTExprCast::Kind::REINTERPRET,
                                         std::move(type), std::move(val));
  }

  else if (tok.type == TOK_SYM_LPAREN) {
    _get_token();
    auto res = _expr();
    _consume_of_type(TOK_SYM_RPAREN, "parse_expr: expected ')'");
    return res;
  } else
    return _expr_symbol();
}

ASTExprPtr Parser::_expr_symbol() // float, int, string, identifier
{
  auto tok = _get_token();
  auto val = tok.val;

  if (tok.type == obcl::TOK_CONST_SQ || tok.type == obcl::TOK_CONST_DQ) {
    val = ASTExprString::decode(val.substr(1, val.size() - 2));
  }

  if (tok.type == obcl::TOK_CONST_FLOAT)
    return std::make_unique<ASTExprFloat>(tok, ASTExprFloat::Type::F64);
  else if (tok.type == obcl::TOK_CONST_INT)
    return std::make_unique<ASTExprInt>(tok, ASTExprInt::Type::I64);
  else if (tok.type == obcl::TOK_ID)
    return std::make_unique<ASTExprId>(tok);
  else if (tok.type == obcl::TOK_CONST_DQ)
    return std::make_unique<ASTExprString>(tok.loc, val);

  throw obcl::ParserError(tok.loc,
                          "parse_expr: expected a constant or identifier");
}

ast_exprs_list_t Parser::_expr_call_list() // expr list (separated by ',')
{
  ast_exprs_list_t res;
  while (true) {
    if (_peek_type() == TOK_SYM_RPAREN)
      break;
    if (!res.empty())
      _consume_of_type(TOK_SYM_COMMA, "parse_expr_call_list: expected ','");

    res.push_back(_expr());
  }

  return res;
}

} // namespace cgen
