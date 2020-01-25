//===--type/type-simple.hh - TypeSimple class definition --------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeSimple
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type.hh"
#include <cstdint>

namespace milk {

/// Parent TypeSimple Class
/// Parent class for all types that are not composed of other recursive types
/// (no function / templates types)
/// eg: native type, struct, refs
class TypeSimple : public Type {
public:
  std::uint32_t code() const { return _code; }

private:
  std::uint32_t _code;

protected:
  /// Each simple type can be represented by a code
  /// The higher byte add some properties to the type (ref, array, const)
  /// The 3 lower bytes is a unique identifier for the type
  TypeSimple(std::uint32_t code) : _code(code) {}
};
} // namespace milk
