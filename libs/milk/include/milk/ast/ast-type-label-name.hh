//===--ast/ast-type-label-name.hh - ASTTypeLabelName class ------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTTypeLabelName
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-type-label.hh"
#include "ast-visitor.hh"
#include <obcl/lexer/token.hh>

namespace milk {

/// AST Node to reference a type simply by it's name (eg u8, void, Point2f, etc)
class ASTTypeLabelName : public ASTTypeLabel {
public:
  ASTTypeLabelName(const obcl::Token &tok)
      : ASTTypeLabelName(tok.loc, tok.val) {}

  ASTTypeLabelName(const obcl::Location &loc, const std::string &name)
      : ASTTypeLabel(loc), _name(name) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }

private:
  std::string _name;
};

} // namespace milk
