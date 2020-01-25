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
#include <unordered_set>
#include <vector>

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

  const TypeFun *type_fun(const Type *ret,
                          const std::vector<const Type *> &args);

  /// Create a new struct type
  /// Because of namespaces, 2 struct with the same \p name may be different
  /// The fields of the struct are defined later
  const TypeStruct *make_type_struct(const std::string &name);

  /// Create a new enum type
  /// Because of namespaces, 2 enums with the same \p name may be different
  const TypeEnum *make_type_enum(const std::string &name,
                                 const TypeNativeInt *actual,
                                 const std::map<std::string, int> &fields);

private:
  std::map<std::uint32_t, const Type *> _val_types;
  std::uint32_t _enum_count;
  std::uint32_t _struct_count;

  TypeBuilder();

  struct TypeFunHash {
    std::size_t operator()(const TypeFun *ty) const noexcept;
  };
  struct TypeFunEq {
    bool operator()(const TypeFun *a, const TypeFun *b) const noexcept;
  };
  std::unordered_set<const TypeFun *, TypeFunHash, TypeFunEq> _funs_table;
};
} // namespace milk
