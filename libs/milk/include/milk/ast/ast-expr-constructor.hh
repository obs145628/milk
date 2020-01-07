//===--ast/ast-expr-constructor.hh - ASTExprConstructor class ---*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTExprConstructor
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include <string>

namespace milk {

/// AST node for a struct instance creation
/// StructName { field1: val1, field2: val2,... }
class ASTExprConstructor : public ASTExpr {
public:
  ASTExprConstructor(const obcl::Location &loc, const std::string &struct_name,
                     ast_exprs_dict_t &&fields)
      : ASTExpr(loc), _struct_name(struct_name), _fields(std::move(fields)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &struct_name() const { return _struct_name; }
  const ast_exprs_dict_t &fields() const { return _fields; }

private:
  std::string _struct_name;
  ast_exprs_dict_t _fields;
};

} // namespace milk
