//===--types/type-error.hh - TypeError class definition ---------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeError
///
//===----------------------------------------------------------------------===//

#pragma once

#include "cgen/ast/fwd.hh"
#include "fwd.hh"
#include <exception>
#include <string>

namespace cgen {

/// General Error for sementic analysis
/// Error inside the source code
class TypeError : public std::exception {

public:
  TypeError(const AST &node, const std::string &method,
            const std::string &mess);

  const char *what() const throw() override { return _str.c_str(); }

private:
  std::string _str;
};

/// Specific kind a type error
/// Happens when the actual type isn't compatible with the expected type
class TypeMismatchError : public TypeError {

public:
  TypeMismatchError(const AST &node, const std::string &method,
                    const Type *type_expect, const Type *type_act);
};

} // namespace cgen
