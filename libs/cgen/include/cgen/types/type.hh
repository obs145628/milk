//===--types/type.hh - Type class definition --------------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class Type
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include <string>

namespace cgen {

/// Represent a data type in the cgen language
/// Parent abstract class, all other types herit from it
/// Type objects created from the TypeBuilder singleton
/// There is only one instance for every type
class Type {
public:
  Type() = default;

  Type(const Type &) = delete;
  Type &operator=(const Type &) = delete;

  virtual ~Type() = default;

  /// @return a string representation of the type
  virtual std::string to_str() const = 0;

  virtual void accept(TypeVisitor &v) const = 0;

private:
};

} // namespace cgen
