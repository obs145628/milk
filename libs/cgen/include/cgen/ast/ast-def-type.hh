//===--ast/ast-def-type.hh - ASTDefTYype class definition -------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTDefType
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def.hh"
#include "ast-visitor.hh"
#include "fwd.hh"
#include <string>

namespace cgen {

/// AST Node to define a type alias
class ASTDefType : public ASTDef {
public:
  ///
  /// @param beg_loc location of the first token of the parsed node
  /// @param end_loc location of the last token of the parsed node
  /// @paran alias new identifier for the alias
  /// @param type aliased typename
  ASTDefType(const obcl::Location &beg_loc, const obcl::Location &end_loc,
             const std::string &alias, ASTTypeIdPtr &&type)
      : ASTDef(obcl::Location(beg_loc, end_loc)), _alias(alias),
        _type(std::move(type)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &alias() const { return _alias; }
  const ASTTypeId &type() const { return *_type; }

private:
  std::string _alias;
  ASTTypeIdPtr _type;
};

} // namespace cgen
