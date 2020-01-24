//===--type/type-builder.hh - TypeBuilder class definition ------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeBuilder
///
//===----------------------------------------------------------------------===//

#pragma once

#include <map>

#include "fwd.hh"

namespace milk {

/// Singleton class
/// Builder pattern for all type classes
/// The builder makes sure there is only instance of the same type to reduce
/// memory usage and allocation
/// What's more using pointers is enough to test if 2 types are exactly the same
class TypeBuilder {
public:
  static TypeBuilder &instance() {
    static TypeBuilder res;
    return res;
  }

  const TypeVoid *type_void();
  const TypeNativeInt *type_u8();
  const TypeNativeInt *type_u16();
  const TypeNativeInt *type_u32();
  const TypeNativeInt *type_u64();
  const TypeNativeInt *type_i8();
  const TypeNativeInt *type_i16();
  const TypeNativeInt *type_i32();
  const TypeNativeInt *type_i64();
  const TypeNativeFloat *type_f32();
  const TypeNativeFloat *type_f64();

  const TypeVal *type_val(const TypeRef *ty);
  const TypeRef *type_mref(const TypeVal *ty);
  const TypeRef *type_cref(const TypeVal *ty);
  const TypeRef *type_amref(const TypeVal *ty);
  const TypeRef *type_acref(const TypeVal *ty);

  const TypeStruct *make_type_struct(const std::string &name);
  const TypeEnum *make_type_enum(const std::string &name,
                                 const TypeNativeInt *actual,
                                 const std::map<std::string, int> &fields);

private:
  std::map<std::uint32_t, const Type *> _val_types;
  std::uint32_t _enum_count;
  std::uint32_t _struct_count;
  TypeBuilder();
};
} // namespace milk
