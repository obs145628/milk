//===--types/type-buiilder.hh - TypeBuilder class definition ----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeBuilder
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type.hh"

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <iostream>

namespace cgen {

/// Singleton class to get type objects
/// There is only one object for every type, and we can get it using this
/// singleton
class TypeBuilder {
public:
  /// @return the singleton instance of TypeBuilder
  static TypeBuilder &instance();

  TypeBuilder(const TypeBuilder &) = delete;
  TypeBuilder &operator=(const TypeBuilder &) = delete;

  ///@{
  /// Functions used to get the id for any type
  /// This strategy of giving one unique id string for every tye may dissapear
  std::string id_void();
  std::string id_u8();
  std::string id_u16();
  std::string id_u32();
  std::string id_u64();
  std::string id_i8();
  std::string id_i16();
  std::string id_i32();
  std::string id_i64();
  std::string id_f32();
  std::string id_f64();
  std::string id_fun(const Type *ret, const std::vector<const Type *> &arg);
  std::string id_ptr(const Type *type);
  std::string id_ref(const Type *type);
  std::string id_struct(const std::string &name);
  ///@}

  const std::string &id_of(const Type *type) const;

  ///@{
  /// Returns type instances for native types
  const Type *type_void();
  const Type *u8();
  const Type *u16();
  const Type *u32();
  const Type *u64();
  const Type *i8();
  const Type *i16();
  const Type *i32();
  const Type *i64();
  const Type *f32();
  const Type *f64();
  ///@}

  /// @returns a function type
  /// @param ret return function type
  /// @param args list of argument types
  const Type *fun(const Type *ret, const std::vector<const Type *> &args);

  /// @returns a ptr to some type
  const Type *ptr(const Type *type);

  /// @returns a ref to some type
  const Type *ref(const Type *type);

  /// @return a struct type
  /// Only the name is needed for a forward declaration
  /// The actual struct fields are defined later
  const Type *type_struct(const std::string &name);

private:
  std::vector<std::unique_ptr<Type>> _defs;
  std::map<std::string, const Type *> _types;
  std::map<const Type *, std::string> _ids_map;

  const Type *_add_type(const std::string &id, Type *raw_ptr);

  TypeBuilder() = default;

public:
  // [TODO] put this on .cc
  void dump_types() const {
    for (const auto &k : _types) {
      std::cout << k.first << " => {" << k.second->to_str() << "}\n";
    }
  }
};

} // namespace cgen
