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
      : ASTTypeLabel(tok.loc), _name(tok.val) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }

private:
  std::string _name;
};

} // namespace milk
