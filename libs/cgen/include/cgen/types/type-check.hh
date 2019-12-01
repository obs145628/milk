//===--types/type-check.hh - Type checker utils -----------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains utilities functions to verify if types are compatible.
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"

namespace cgen {
namespace type_check {

/// Check if type \p act can be converted to type \p exp.
/// This is only an implicit conversion, doesn't change type
/// do not perform any operation
/// TODO: right now really simple version
/// &T => T
bool match(const Type *exp, const Type *act);

/// check if both types are exactly the same
bool equals(const Type *t1, const Type *t2);

} // namespace type_check
} // namespace cgen
