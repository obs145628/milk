//===--type/type-native.hh - TypeNative class definition ---------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeNative, and all its
/// subclasses
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type-val.hh"
#include "type-visitor.hh"

namespace milk {

/// Abstract TypeNative Class
/// Parent for all native basic numeric types of the language: u8, u16, i32,
/// f32, etc
class TypeNative : public TypeVal {
protected:
  TypeNative(std::uint32_t code) : TypeVal(code) {}
};

/// Represent all signed and unsigned int types
/// i8, i16, i32, i64, u8, u16, u32, u64
class TypeNativeInt : public TypeNative {
public:
  enum class Kind { I8, I16, I32, I64, U8, U16, U32, U64 };

  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  Kind _kind;

  TypeNativeInt(std::uint32_t code, Kind kind)
      : TypeNative(code), _kind(kind) {}
};

/// Represent all floating points types
/// f32, f64
class TypeNativeFloat : public TypeNative {
public:
  enum class Kind { F32, F64 };

  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  Kind _kind;

  TypeNativeFloat(std::uint32_t code, Kind kind)
      : TypeNative(code), _kind(kind) {}
};

} // namespace milk
