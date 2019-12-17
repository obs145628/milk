//===--ast/ast-def-struct.hh - ASTDefStruct class definition -----*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTDefStruct
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-visitor.hh"
#include "ast.hh"
#include <string>

namespace milk {

/// Represent a struct definition, with all its fields
class ASTDefStruct : public AST {
public:
  /// @param beg_loc location of 'struct'
  /// @param end_loc location of ';'
  ASTDefStruct(const obcl::Location &beg_loc, const obcl::Location &end_loc,
               const std::string &name, ast_defs_list_t &&fields)
      : AST(obcl::Location(beg_loc, end_loc)), _name(name),
        _fields(std::move(fields)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ast_defs_list_t &fields() const { return _fields; }

private:
  std::string _name;
  ast_defs_list_t _fields;
};

} // namespace milk
