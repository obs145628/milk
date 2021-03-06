//===--type/type-enum.hh - TypeEnum class definition ------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeEnum
///
//===----------------------------------------------------------------------===//

#pragma once

#include <map>
#include <string>

#include "fwd.hh"
#include "type-val.hh"
#include "type-visitor.hh"

namespace milk {

/// Class to represent all user-defined enum types
class TypeEnum : public TypeVal {
public:
  const std::string &name() const { return _name; }

  /// Return the actual int type used for the enum implementation
  const TypeNativeInt *actual() const { return _actual; }

  const std::map<std::string, int> &fields() const { return _fields; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  std::string _name;
  const TypeNativeInt *_actual;
  std::map<std::string, int> _fields;

private:
  TypeEnum(std::uint32_t code, const std::string &name,
           const TypeNativeInt *actual,
           const std::map<std::string, int> &fields)
      : TypeVal(code), _name(name), _actual(actual), _fields(fields) {}

  friend TypeBuilder;
};
} // namespace milk
