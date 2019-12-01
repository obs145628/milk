//===--types/type-ptr.hh - TypePtr class definition -------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypePtr
///
//===----------------------------------------------------------------------===//

#pragma once

#include "type-visitor.hh"
#include "type.hh"

namespace cgen {

/// Represent a value containing an adress to a value of another type
class TypePtr : public Type {
  friend class TypeBuilder;

private:
  TypePtr(const Type *type) : _type(type) {}

public:
  std::string to_str() const override { return _type->to_str() + "*"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }

  const Type *type() const { return _type; }

private:
  const Type *_type;
};

} // namespace cgen
