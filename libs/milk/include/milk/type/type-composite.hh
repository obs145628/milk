//===--type/type-composite.hh - TypeComposite class definition --*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeComposite
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type.hh"

namespace milk {

/// Parent TypeComposite Class
/// Parent class for all types that are composed of other recursive types
/// eg: function / templates types
class TypeComposite : public Type {
public:
  TypeComposite() = default;

private:
};
} // namespace milk
