#include "parser/parser.hh"
#include "parser/parser-error.hh"

namespace obcl {

Token Parser::_consume_of_type(token_type_t type, const std::string &mess) {
  auto tok = _lex.get_token();
  if (tok.type != type)
    throw ParserError(tok.loc, mess);
  return tok;
}

token_type_t Parser::_peek_type() { return _lex.peek_token().type; }

} // namespace obcl
