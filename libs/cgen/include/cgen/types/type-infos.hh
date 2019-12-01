//===--types/type-infos.hh - utils for Type objects -------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains multiple utils functions and definitions to manipulate
/// Type objects
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"

namespace cgen {

namespace type_infos {

using TypeBool = TypeI32;
using typeChar = TypeI8;
using TypeIsize = TypeI64;
using TypeUSize = TypeU64;

bool is_fun(const Type &t);
bool is_void(const Type &t);
bool is_numeric(const Type &t);
bool is_int(const Type &t);
bool is_float(const Type &t);
bool is_ptr(const Type &t);
bool is_ref(const Type &t);
bool is_struct(const Type &t);

const Type *type_bool();
const Type *type_char();
const Type *type_isize();
const Type *type_usize();

/// convert a type to a ref
/// makes sure to not create a ref of ref
const Type *to_ref(const Type *t);

/// remove ref is there is one
const Type *to_val(const Type *t);

/// @return the type size, or -1 if unknown ()
/// [TODO] I am still not sure, should struct size be known now or later in
/// compilation
int size(const Type *t);

} // namespace type_infos

} // namespace cgen
