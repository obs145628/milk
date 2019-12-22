//===--ast/ast-def-alias.hh - ASTDefAlias class definition -----------------*-
// C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTDefAlias
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def.hh"
#include "ast-visitor.hh"
#include <string>

namespace milk {

/// AST Node to defined a type alias
/// eg: type counter_t = i16;
class ASTDefAlias : public ASTDef {
public:
  ASTDefAlias(const obcl::Location &beg_loc, const obcl::Location &end_loc,
              const std::string &name, ASTTypeLabelPtr &&type)
      : ASTDef(obcl::Location(beg_loc, end_loc)), _name(name),
        _type(std::move(type)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ASTTypeLabel &type() const { return *_type; }

private:
  std::string _name;
  ASTTypeLabelPtr _type;
};

} // namespace milk
