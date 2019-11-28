//===--ast/ast-expr-sizeof.hh - ASTExprSizeof class definition --*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprSizeof
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-type-id.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST Node for sizeof expr
/// [TODO]: maybe remove it in the future
class ASTExprSizeof : public ASTExpr {

public:
  ///
  /// @param beg_loc location of the first token of the parsed node
  /// @param type typename for the type you want to know the size
  ASTExprSizeof(const obcl::Location &beg_loc, ASTTypeIdPtr &&type)
      : ASTExpr(obcl::Location(beg_loc, type->loc())), _type(std::move(type)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTTypeId &type() const { return *_type; }

private:
  ASTTypeIdPtr _type;
};

} // namespace cgen
