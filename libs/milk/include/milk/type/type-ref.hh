//===--type/type-ref.hh - TypeRef class definition --------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeRef
///
//===----------------------------------------------------------------------===//

#pragma once

#include <vector>

#include "fwd.hh"
#include "type-simple.hh"
#include "type-visitor.hh"

namespace milk {

/// Class to represent the 4 kind of refs in Milk
/// & T, &const T, &[] T, &[]const T
class TypeRef : public TypeSimple {
public:
  enum class Kind {
    MREF,  //& T
    CREF,  //&const T
    AMREF, //&[] T,
    ACREF, //&[]const T
  };

  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  const TypeVal *_type_val;
  Kind _kind;

private:
  TypeRef(int code, const TypeVal *type_val, Kind kind)
      : TypeSimple(code), _type_val(type_val), _kind(kind) {}

  friend TypeBuilder;
};
} // namespace milk
