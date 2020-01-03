#include "lexer/token.hh"
#include "utils/debug.hh"
#include <cassert>

namespace obcl {

const char *Token::type_str() const {
  const auto &reprs = _get_type_reprs();
  auto it = reprs.find(type);
  assert(it != reprs.end());
  return it->second;
}

long Token::get_int() const {
  assert(type == TOK_CONST_INT);
  return std::stol(val);
}

double Token::get_float() const {
  assert(type == TOK_CONST_FLOAT);
  return std::stod(val);
}

int Token::get_char() const {
  assert(type == TOK_CONST_SQ);
  if (val[1] == '\\') {
    switch (val[2]) {
    case 'n':
      return '\n';
    case 't':
      return '\t';
    default:
      UNREACHABLE();
    }
  }

  return val[1];
}

void Token::add_type(token_type_t type, const char *repr) {
  auto &reprs = _get_type_reprs();
  assert(reprs.find(type) == reprs.end());
  reprs.insert({type, repr});
}

std::map<token_type_t, const char *> &Token::_get_type_reprs() {
  static std::map<token_type_t, const char *> res = {
      {TOK_ERR, "ERR"},
      {TOK_EOF, "EOF"},
      {TOK_CONST_SQ, "CONST_SQ"},
      {TOK_CONST_DQ, "CONST_DQ"},
      {TOK_CONST_INT, "CONST_INT"},
      {TOK_CONST_FLOAT, "CONST_FLOAT"},
      {TOK_ID, "ID"}};

  return res;
}

std::ostream &operator<<(std::ostream &os, const Token &tok) {
  return os << "{" << tok.type_str() << "(" << tok.val << "):" << tok.loc
            << "}";
}

} // namespace obcl
