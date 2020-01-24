//===--type/type-void.hh - TypeVoid class definition -------------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeVoid
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type-codes.hh"
#include "type-simple.hh"
#include "type-visitor.hh"

namespace milk {

/// Represent the basic void type
class TypeVoid : public TypeSimple {
private:
  TypeVoid() : TypeSimple(typecode::CODE_VOID) {}

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

  friend TypeBuilder;
};

} // namespace milk
