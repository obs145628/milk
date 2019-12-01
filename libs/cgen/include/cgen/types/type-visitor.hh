//===--types/type-visitor.hh - TypeVisitor class definition -----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeVisitor
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "type.hh"

namespace cgen {

/// Implement of the visitor design pattern for the type hierarchy
/// This default visitor does nothing
class TypeVisitor {
public:
  virtual ~TypeVisitor() = default;
  void operator()(const Type &t) { accept(t); }
  void accept(const Type &t) { t.accept(*this); }

  virtual void visit(const TypeFun &t);
  virtual void visit(const TypeVoid &t);
  virtual void visit(const TypeU8 &t);
  virtual void visit(const TypeU16 &t);
  virtual void visit(const TypeU32 &t);
  virtual void visit(const TypeU64 &t);
  virtual void visit(const TypeI8 &t);
  virtual void visit(const TypeI16 &t);
  virtual void visit(const TypeI32 &t);
  virtual void visit(const TypeI64 &t);
  virtual void visit(const TypeF32 &t);
  virtual void visit(const TypeF64 &t);
  virtual void visit(const TypePtr &t);
  virtual void visit(const TypeRef &t);
  virtual void visit(const TypeStruct &t);
};

} // namespace cgen
