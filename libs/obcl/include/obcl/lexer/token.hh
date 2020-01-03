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

  /// @returns an EOF token
  /// This token is special, it's the only one connected to no stream
  static Token eof() {
    Position pos0(0, 0, 0, nullptr);
    return Token(Location(pos0, pos0), TOK_EOF, "");
  }

  /// \returns a string representation of the token type
  const char *type_str() const;

  /// token must be of type CONST_INT
  /// \returns the int value
  long get_int() const;

  /// token must be of type CONST_FLOAT
  /// \returns the double value
  double get_float() const;

  /// token must of type CONST_SQ
  /// \returns the actual char inside the
  int get_char() const;

  /// add a new custom token type
  /// @param repr - string representation, for debug porposes. Should be a
  /// static string
  static void add_type(token_type_t type, const char *repr);

private:
  static std::map<token_type_t, const char *> &_get_type_reprs();
};

/// Dump a Token. for debug purposes only
std::ostream &operator<<(std::ostream &os, const Token &tok);

} // namespace obcl
