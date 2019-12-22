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
  auto tok = _lex.peek_token();
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

} // namespace milk
