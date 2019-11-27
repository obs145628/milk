//===-- lexer/stream.hh - Lexer class definition ----------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class Lexer
///
//===----------------------------------------------------------------------===//

#pragma once

#include "stream.hh"
#include "token.hh"
#include "trie.hh"
#include <map>
#include <memory>
#include <set>

namespace obcl {

/// This is a generic Lexer
/// It manages one or multiple stream of different types
/// (file, raw string)
/// It gives a stream of Tokens (peek or consume last token)
/// Tokens are basic types:
/// - integer
/// - float
/// - strings (single or double quotes)
/// - identifiers
///
/// It's also possible to add customs tokens with a fixed syntax
/// They are different kinds:
/// - custom tokens that doesn't start like an identifier:
/// These are usualy used for operators ('+', '==') or language separators (';',
/// ':', '{', '}') It match the longest one find
/// - custom token that are identifiers
/// These are usually used for keywords ('for', 'function', 'return')
/// - it first find the longest possible id. Then if it's a custom id it returns
/// it, iotherwhise it returns a general id
class Lexer {
public:
  struct CustomTokenInfos {
    token_type_t type_id;

    /// What the lexer is trying to find on the stream
    const char *val;

    const char *repr;
  };

  /// Create a new Lexer, without any associated stream
  /// Without stream. the token always gives EOF tokens
  /// Use set_stream_xxx methods to add a stream
  ///
  /// @param custom static array with infos on custom tokens
  /// The next to  last element of the array has a type_id of 0
  /// This constructor calls Token::add_type() for all custom tokens
  /// Panic if the custom contain some token values not supported
  Lexer(const CustomTokenInfos *custom);

  Lexer(const Lexer &) = delete;
  Lexer(Lexer &&) = default;

  /// Set the stream to a source file
  /// @param path relative path to the source file
  /// The lexer must have no stream or a finished one (reached EOF)
  /// Otherwhise this method panics
  void set_stream_file(const std::string &path);

  /// Set the stream to a raw string of source code
  /// The lexer must have no stream or a finished one (reached EOF)
  /// Otherwhise this method panics
  void set_stream_raw(const std::string &str);

  /// Remove the current stream of the Lexer
  /// Without stream. the token always gives EOF tokens
  void reset_stream();

  /// Get a peek at the next token (don't consume it)
  /// @returns EOF if there is no stream
  Token peek_token();

  /// Consume and returns the next token
  /// @returns EOF if there is no stream
  Token get_token();

  /// check if the current token is end of file
  bool is_eof();

private:
  /// fill the _peek token, unless it's already filled
  void _fetch_peek();

  /// read the next token from the current top stream
  /// return eof if there is no available token
  /// throws LexerError if cannot parse a token
  Token _read_token();

  /// Read string contaimed within matching ' or "
  Token _read_string();

  /// Read multiple kinds of numbers:
  /// integers: [0-9]+
  /// floats: [0-9]+[.][0-9]*
  Token _read_number();

  /// Read a custom token
  /// First char doesn't start as an identifier
  Token _read_custom_nonidstart();

  /// Read either a custom token that is an id, or an identifier
  /// [a-zA-Z_$][a-zA-Z0-9_$]*
  Token _read_id_or_custom_id();

  std::unique_ptr<Stream> _stream;
  Token _peek;

  std::map<std::string, token_type_t> _custom_id;
  Trie _trie_nonid;
  // std::set<std::string> _custom_set;
  // std::map<std::string, token_type_t> _custom_ids;
};

} // namespace obcl
