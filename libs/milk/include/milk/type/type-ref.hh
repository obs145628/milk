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

  const Type *val_type() const { return _val_type; }
  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  const Type *_val_type;
  Kind _kind;

private:
  TypeRef(int code, const Type *val_type, Kind kind)
      : TypeSimple(code), _val_type(val_type), _kind(kind) {}
};
} // namespace milk
