//===--type/type-visitor.hh - TypeVisitor class definition ------*- C++ -*-===//
//
// milk compiler library
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

namespace milk {

/// Implementation of the visitor design pattern for the Type classes hierarchy
/// When called with a Type&, dispatch it to the visit method for the right type
/// The default implementation simply visit the children
/// You must create a child class, and override the visit methods
class TypeVisitor {
public:
  virtual ~TypeVisitor() = default;

  /// Performs dynamic dispatch of \p type to the right visit() method
  void operator()(const Type *t) { accept(t); }

  /// Performs dynamic dispatch of \p ast to the right visit() method
  void accept(const Type *t) { t->accept(*this); }

  // default visitors, recursive call through children
  virtual void visit(const TypeEnum &t);
  virtual void visit(const TypeFun &t);
  virtual void visit(const TypeNativeFloat &t);
  virtual void visit(const TypeNativeInt &t);
  virtual void visit(const TypeRef &t);
  virtual void visit(const TypeStruct &t);
  virtual void visit(const TypeVoid &t);

private:
};

} // namespace milk
