//===--ast/ast-def-var.hh - ASTDefVar class definition ----------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTDefVar
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def.hh"
#include "ast-visitor.hh"
#include "fwd.hh"
#include <string>

namespace cgen {

/// AST Class for a variable definition
/// Can be used for local or global variables
class ASTDefVar : public ASTDef {
public:
  ///
  /// @param beg_loc location of the first token of the parsed node
  /// @param end_loc location of the last token of the parsed node
  /// @paran name identifier name for the variable
  /// @param type typename of the variable
  /// @param val optional initival value for the variable
  ASTDefVar(const obcl::Location &beg_loc, const obcl::Location &end_loc,
            const std::string &name, ASTTypeIdPtr &&type, ASTExprPtr val)
      : ASTDef(obcl::Location(beg_loc, end_loc)), _name(name),
        _type(std::move(type)), _val(std::move(val)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ASTTypeId &type() const { return *_type; }
  const ASTExpr &val() const { return *_val; }
  bool has_val() const { return _val.get(); }

private:
  std::string _name;
  ASTTypeIdPtr _type;
  ASTExprPtr _val;
};

} // namespace cgen
