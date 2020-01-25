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
#include "type-codes.hh"
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

  static std::uint32_t kind2attr(Kind kind);

  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  const TypeVal *_type_val;
  Kind _kind;

private:
  TypeRef(const TypeVal *type_val, Kind kind)
      : TypeSimple(typecode::build_code(type_val->code(), kind2attr(kind))),
        _type_val(type_val), _kind(kind) {}

  friend TypeBuilder;
};

inline std::uint32_t TypeRef::kind2attr(Kind kind) {
  switch (kind) {
  case Kind::MREF:
    return typecode::ATTR_MREF;
  case Kind::CREF:
    return typecode::ATTR_CREF;
  case Kind::AMREF:
    return typecode::ATTR_AMREF;
  case Kind::ACREF:
    return typecode::ATTR_ACREF;
  }
}

} // namespace milk
