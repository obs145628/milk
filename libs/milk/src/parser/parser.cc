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

} // namespace milk
