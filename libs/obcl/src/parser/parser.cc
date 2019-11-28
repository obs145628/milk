#include "parser/parser.hh"
#include "parser/parser-error.hh"

namespace obcl {

Token Parser::_consume_of_type(token_type_t type, const std::string &mess) {
  auto tok = _lex.get_token();
  if (tok.type != type)
    throw ParserError(tok.loc, mess);
  return tok;
}

Token Parser::_consume_id(const std::string &mess) {
  return _consume_of_type(TOK_ID, mess);
}

bool Parser::_consume_if_type(token_type_t type) {
  auto tok = _lex.peek_token();
  if (tok.type != type)
    return false;
  _lex.get_token();
  return true;
}

token_type_t Parser::_peek_type() { return _lex.peek_token().type; }

} // namespace obcl
