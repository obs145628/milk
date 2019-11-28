//===--ast/ast-def-struct.hh - ASTDefStruct class definition ----*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTDefStruct
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def.hh"
#include "ast-visitor.hh"
#include "fwd.hh"
#include <string>
#include <utility>
#include <vector>

namespace cgen {

/// AST Node to represnt a struct definition
class ASTDefStruct : public ASTDef {
public:
  ///
  /// @param beg_loc location of the first token of the parsed node
  /// @param end_loc location of the last token of the parsed node
  /// @param name identifier name for the struct type
  /// @param fields list of the struct fields
  ASTDefStruct(const obcl::Location &beg_loc, const obcl::Location &end_loc,
               const std::string &name, ast_args_def_t &&fields)
      : ASTDef(obcl::Location(beg_loc, end_loc)), _name(name),
        _fields(std::move(fields)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ast_args_def_t &fields() const { return _fields; }

  std::string def_name() const { return "__cgen__" + _name; }

private:
  std::string _name;
  ast_args_def_t _fields;
};

} // namespace cgen
