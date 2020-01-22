//===--type/type-val.hh - TypeVal class definition --------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeVal
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type-simple.hh"

namespace milk {

/// Anstract TypeVal Class
/// Parent class for all types that are a simple value
/// native type, structs and enums
class TypeVal : public TypeSimple {
public:
  TypeVal(std::uint32_t code) : TypeSimple(code) {}

private:
};
} // namespace milk
