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

  /// consume the next token
  /// throws a ParserError if not of correct type
  /// mess is only used to describe errpr
  Token _consume_of_type(token_type_t type, const std::string &mess);

  // try to consume a token as an identifier
  // throws a ParserError if invalid token
  // mess only used to describe errpr
  Token _consume_id(const std::string &mess);

  /// If the next token type is \p type, consumes it
  /// Otherwhise doesn nothing
  /// Returns if the token was consumed
  bool _consume_if_type(token_type_t type);

  /// @returns the type of the current token
  /// Doesn't cunsome it
  token_type_t _peek_type();
};

} // namespace obcl
