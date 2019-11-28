//===-- parser/parser-error.hh - ParrserError class definition ---*- C++-*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ParserError
///
//===----------------------------------------------------------------------===//

#pragma once

#include "../lexer/fwd.hh"
#include <exception>
#include <string>

namespace obcl {

/// Compiler error caused by user input error
/// During the parsing stage, when trying to build the AST
class ParserError : public std::exception {
public:
  ParserError(const Location &loc, const std::string &mess);

  const char *what() const throw() override { return _str.c_str(); }

private:
  std::string _str;
};

} // namespace obcl
