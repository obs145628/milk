//===--ast/ast-type-id-pointer.hh - ASTTypeIdPointer class ------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTTypeIdPointer
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-type-id.hh"
#include <string>

namespace cgen {

/// AST Node for a typename pointer
class ASTTypeIdPointer : public ASTTypeId {
public:
  /// @param end_loc location of '*'
  ASTTypeIdPointer(const obcl::Location &end_loc, ASTTypeIdPtr &&type)
      : ASTTypeId(obcl::Location(type->loc(), end_loc)),
        _type(std::move(type)) {}

  const ASTTypeId &type() const { return *_type; }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

private:
  ASTTypeIdPtr _type;
};

} // namespace cgen
