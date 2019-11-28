//===--ast/ast-type-id-name.hh - ASTTypeIdName class definition -*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTTypeIdName
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-type-id.hh"
#include "obcl/lexer/token.hh"

namespace cgen {

/// AST Node to represent a typename with a simple identifier
class ASTTypeIdName : public ASTTypeId {
public:
  ASTTypeIdName(const obcl::Token &tok) : ASTTypeId(tok.loc), _name(tok.val) {}

  const std::string &name() const { return _name; }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

private:
  std::string _name;
};

} // namespace cgen
