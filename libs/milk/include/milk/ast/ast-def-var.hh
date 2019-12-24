//===--ast/ast-def-var.hh - ASTDefVar class definition -----------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTDefVar
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def.hh"
#include "ast-visitor.hh"
#include <string>

namespace milk {

/// Represent a variable definition. Can be used in several cases:
/// - struct field definition
class ASTDefVar : public ASTDef {
public:
  enum class Kind { STRUCT_FIELD };

  ASTDefVar(const obcl::Location &loc, Kind kind, ASTNamedStoragePtr &&storage)
      : ASTDef(loc), _kind(kind), _storage(std::move(storage)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  const ASTNamedStorage &storage() const { return *_storage; }

private:
  Kind _kind;
  ASTNamedStoragePtr _storage;
};

} // namespace milk
