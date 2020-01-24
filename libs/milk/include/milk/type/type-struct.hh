//===--type/type-struct.hh - TypeStruct class definition --------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeStruct
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cassert>
#include <map>
#include <string>

#include "fwd.hh"
#include "type-val.hh"
#include "type-visitor.hh"

namespace milk {

/// Class to represent a struct
/// All types object are imutables, but at first the struct fields are unknown
/// So we can set the fields only once, using a const function
class TypeStruct : public TypeVal {
public:
  bool is_defined() const { return _defined; }

  const std::map<std::string, const Type *> &fields() const {
    assert(_defined);
    return _fields;
  }

  const std::string &name() const { return _name; }

  /// Declare fields types after type creation
  /// Can be called only once
  void declare_fields(const std::map<std::string, const Type *> &fields) const {
    assert(!_defined);
    _fields = fields;
  }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  mutable bool _defined;
  mutable std::map<std::string, const Type *> _fields;
  std::string _name;

private:
  TypeStruct(std::uint32_t code, const std::string &name)
      : TypeVal(code), _defined(false), _name(name) {}

  friend TypeBuilder;
};
} // namespace milk
