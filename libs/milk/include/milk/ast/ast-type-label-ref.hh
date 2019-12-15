//===--ast/ast-type-label-ref.hh - ASTTypeLabelRef class --------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTTypeLabelRef
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-type-label.hh"
#include "ast-visitor.hh"

namespace milk {

/// AST Node to reference a type simply by it's name (eg u8, void, Point2f, etc)
class ASTTypeLabelRef : public ASTTypeLabel {
public:
  enum class Kind { MUT_REF, CONST_REF, MUT_ARR_REF, CONST_ARR_REF };

  /// param beg_loc location of reference type token
  ASTTypeLabelRef(const obcl::Location &beg_loc, Kind kind,
                  ASTTypeLabelPtr &&type)
      : ASTTypeLabel(obcl::Location(beg_loc, type->loc())), _kind(kind),
        _type(std::move(type)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  const ASTTypeLabel &type() const { return *_type; }

private:
  Kind _kind;
  ASTTypeLabelPtr _type;
};

} // namespace milk
