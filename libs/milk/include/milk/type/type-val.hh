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
protected:
  TypeVal(std::uint32_t code)
      : TypeSimple(code), _type_mref(nullptr), _type_cref(nullptr),
        _type_amref(nullptr), _type_acref(nullptr) {}

private:
  mutable const TypeRef *_type_mref;
  mutable const TypeRef *_type_cref;
  mutable const TypeRef *_type_amref;
  mutable const TypeRef *_type_acref;

  friend TypeBuilder;
};
} // namespace milk
