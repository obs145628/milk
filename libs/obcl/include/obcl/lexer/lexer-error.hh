//===-- lexer/token.hh - LexerError struct definition -----------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class LexerError
/// Inherits from std::exception
///
//===----------------------------------------------------------------------===//

#pragma once

#include "location.hh"
#include <exception>
#include <string>

namespace obcl {

/// Compiler Error caused by invalid user input
/// The lexer cannot build the next token
class LexerError : public std::exception {
public:
  /// @param loc - Location of the string the lexer couldn't parse
  /// @param mess - Error message with context details
  LexerError(const Location &loc, const std::string &mess);

  const char *what() const throw() override { return _str.c_str(); }

private:
  std::string _str;
};

} // namespace obcl
