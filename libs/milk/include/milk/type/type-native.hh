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
#include "type-codes.hh"
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

  static int kind2code(Kind kind);

  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  Kind _kind;

  TypeNativeInt(Kind kind) : TypeNative(kind2code(kind)), _kind(kind) {}

  friend TypeBuilder;
};

/// Represent all floating points types
/// f32, f64
class TypeNativeFloat : public TypeNative {
public:
  enum class Kind { F32, F64 };

  static int kind2code(Kind kind);

  Kind kind() const { return _kind; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  Kind _kind;

  TypeNativeFloat(Kind kind) : TypeNative(kind2code(kind)), _kind(kind) {}

  friend TypeBuilder;
};

inline int TypeNativeInt::kind2code(Kind kind) {
  switch (kind) {
  case Kind::U8:
    return typecode::CODE_U8;
  case Kind::U16:
    return typecode::CODE_U16;
  case Kind::U32:
    return typecode::CODE_U32;
  case Kind::U64:
    return typecode::CODE_U64;
  case Kind::I8:
    return typecode::CODE_I8;
  case Kind::I16:
    return typecode::CODE_I16;
  case Kind::I32:
    return typecode::CODE_I32;
  case Kind::I64:
    return typecode::CODE_I64;
  }
}

inline int TypeNativeFloat::kind2code(Kind kind) {
  switch (kind) {
  case Kind::F32:
    return typecode::CODE_F32;
  case Kind::F64:
    return typecode::CODE_F64;
  }
}

} // namespace milk
