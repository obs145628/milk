//===-- lexer/token.hh - Token struct definition ----------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the struct Token
///
//===----------------------------------------------------------------------===//

#pragma once

#include "location.hh"
#include <map>
#include <ostream>
#include <string>

namespace obcl {

/// default token types
constexpr token_type_t TOK_ERR = 1;
constexpr token_type_t TOK_EOF = 2;
constexpr token_type_t TOK_CONST_SQ = 3;
constexpr token_type_t TOK_CONST_DQ = 4;
constexpr token_type_t TOK_CONST_INT = 5;
constexpr token_type_t TOK_CONST_FLOAT = 6;
constexpr token_type_t TOK_ID = 7;

/// the token is the atom for the parser
/// the program source is represented as a sequence of tokens
/// they are some common default token types
/// it's possible to add custom ones
struct Token {
  Location loc;
  token_type_t type;
  std::string val;

  Token(const Location &loc, token_type_t type, const std::string &val)
      : loc(loc), type(type), val(val) {}

  /// \returns a string representation of the token type
  const char *type_str() const;

  /// token must be of type CONST_INT
  /// \returns the int value
  long get_int() const;

  /// token must be of type CONST_FLOAT
  /// \returns the double value
  double get_float() const;

  /// add a new custom token type
  static void add_type(token_type_t type, const char *repr);

private:
  static std::map<token_type_t, const char *> _type_reprs;
};

/// Dump a Token. for debug purposes only
std::ostream &operator<<(std::ostream &os, const Token &tok);

} // namespace obcl
