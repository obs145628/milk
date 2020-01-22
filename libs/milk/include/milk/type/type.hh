//===--type/type.hh - Type class definition ---------------------*- C++ -*-===//
//
// milk compiler library
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

namespace milk {

/// Parent Type Class
/// Represent a type in Milk language
class Type {
public:
  Type() = default;
  Type(const Type &) = delete;

  virtual void accept(TypeVisitor &visitor) const = 0;

private:
};
} // namespace milk
