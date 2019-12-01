//===--types/type-numeric.hh - numeric types class definitions ---*- C++
//-*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declarations of all the numeric types classes
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type-visitor.hh"
#include "type.hh"

namespace cgen {

class TypeVoid : public Type {
  friend class TypeBuilder;

private:
  TypeVoid() = default;

public:
  std::string to_str() const override { return "void"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeU8 : public Type {
  friend class TypeBuilder;

private:
  TypeU8() = default;

  std::string to_str() const override { return "u8"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeU16 : public Type {
  friend class TypeBuilder;

private:
  TypeU16() = default;

  std::string to_str() const override { return "u16"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeU32 : public Type {
  friend class TypeBuilder;

private:
  TypeU32() = default;

  std::string to_str() const override { return "u32"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeU64 : public Type {
  friend class TypeBuilder;

private:
  TypeU64() = default;

  std::string to_str() const override { return "u64"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeI8 : public Type {
  friend class TypeBuilder;

private:
  TypeI8() = default;

  std::string to_str() const override { return "i8"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeI16 : public Type {
  friend class TypeBuilder;

private:
  TypeI16() = default;

  std::string to_str() const override { return "i16"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeI32 : public Type {
  friend class TypeBuilder;

private:
  TypeI32() = default;

  std::string to_str() const override { return "i32"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeI64 : public Type {
  friend class TypeBuilder;

private:
  TypeI64() = default;

  std::string to_str() const override { return "i64"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeF32 : public Type {
  friend class TypeBuilder;

private:
  TypeF32() = default;

public:
  std::string to_str() const override { return "f32"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

class TypeF64 : public Type {
  friend class TypeBuilder;

private:
  TypeF64() = default;

public:
  std::string to_str() const override { return "f64"; }

  void accept(TypeVisitor &v) const override { v.visit(*this); }
};

} // namespace cgen
