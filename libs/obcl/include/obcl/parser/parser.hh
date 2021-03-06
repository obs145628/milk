//===-- parser/parser.hh - Parrser class definition --------------*- C++-*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class Parser
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../lexer/lexer.hh"
#include "../parser/parser-error.hh"
#include <initializer_list>
#include <set>
#include <string>

namespace obcl {

/// Very basic parser class
/// Wrapper around a lexer (countains a Lexer object)
/// Doesn't do much by itself
/// It just has some methods related to the lexer
/// And some general helper methods usefull for parsing
/// Hand-written parser inherits from this class
class Parser {

public:
  /// Forward parameters to the lexer constructor
  Parser(const Lexer::CustomTokenInfos *custom) : _lex(custom) {}

protected:
  Lexer _lex;

  /// Convenient shortcut for _lex.peek_token()
  Token _peek_token() { return _lex.peek_token(); }

  /// Convenient shortcut for _lex.get_token()
  Token _get_token() { return _lex.get_token(); }

  /// @returns the type of the current token
  /// Doesn't cunsome it
  token_type_t _peek_type() { return _peek_token().type; }

  /// consume the next token
  /// throws a ParserError if not of correct type
  /// mess is only used to describe errpr
  Token _consume_of_type(token_type_t type, const std::string &mess);
  Token _consume_of_type(const std::initializer_list<token_type_t> &types,
                         const std::string &mess);

  // try to consume a token as an identifier
  // throws a ParserError if invalid token
  // mess only used to describe errp
  std::string _consume_id(const std::string &mess);

  // try to consume a token as a constant integer
  // throws a ParserError if invalid token
  // mess only used to describe errp
  long _consume_cint(const std::string &mess);

  /// If the next token type is \p type, consumes it
  /// Otherwhise doesn nothing
  /// @param out_tok if not null, store tje consumed token
  /// Returns true if the token was consumed
  bool _consume_if_type(token_type_t type, Token *out_tok = nullptr);
  bool _consume_if_type(const std::initializer_list<token_type_t> &types,
                        Token *out_tok = nullptr);

  /// @returns true if the current token is one of the types
  /// Doesn't consume it
  bool _peek_any_of(const std::initializer_list<token_type_t> &types);
};

inline Token Parser::_consume_of_type(token_type_t type,
                                      const std::string &mess) {
  auto tok = _lex.get_token();
  if (tok.type != type)
    throw ParserError(tok.loc, mess);
  return tok;
}

inline Token
Parser::_consume_of_type(const std::initializer_list<token_type_t> &types,
                         const std::string &mess) {
  if (!_peek_any_of(types))
    throw ParserError(_peek_token().loc, mess);
  return _get_token();
}

inline std::string Parser::_consume_id(const std::string &mess) {
  return _consume_of_type(TOK_ID, mess).val;
}

inline long Parser::_consume_cint(const std::string &mess) {
  return _consume_of_type(TOK_CONST_INT, mess).get_int();
}

inline bool Parser::_consume_if_type(token_type_t type, Token *out_tok) {
  if (_peek_type() != type)
    return false;
  auto tok = _lex.get_token();
  if (out_tok)
    *out_tok = tok;
  return true;
}

inline bool
Parser::_consume_if_type(const std::initializer_list<token_type_t> &types,
                         Token *out_tok) {
  if (!_peek_any_of(types))
    return false;
  auto tok = _lex.get_token();
  if (out_tok)
    *out_tok = tok;
  return true;
}

inline bool
Parser::_peek_any_of(const std::initializer_list<token_type_t> &types) {
  auto ptype = _peek_type();
  for (const auto &t : types)
    if (t == ptype)
      return true;
  return false;
}

} // namespace obcl
