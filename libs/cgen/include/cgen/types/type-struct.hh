//===--types/type-struct.hh - TypeStruct class definition -------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeStruct
///
//===----------------------------------------------------------------------===//

#pragma once

#include "type-visitor.hh"
#include "type.hh"

#include <cassert>
#include <map>
#include <string>

namespace cgen {

/// Represents a struct type
/// In cgen, a struct is identified by it's name, not by the type of its fields
class TypeStruct : public Type {
  friend class TypeBuilder;

private:
  TypeStruct(const std::string &name) : _name(name), _fields(), _defined() {}

public:
  // we first create an empty struct
  // then add its definiton later

  bool defined() const { return _defined; }

  void make_def(const std::map<std::string, const Type *> &fields) const {
    assert(!_defined);
    _fields = fields;
    _defined = true;
  }

  std::string to_str() const override { return "struct " + _name; }

  const std::string &name() const { return _name; }
  const std::map<std::string, const Type *> &fields() const { return _fields; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }

private:
  std::string _name;
  mutable std::map<std::string, const Type *> _fields;
  mutable bool _defined;
};

} // namespace cgen
