//===--ast/ast-def-enum.hh - ASTDefEnum class definition ---------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTDefEnum
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-visitor.hh"
#include "ast.hh"
#include <string>
#include <utility>
#include <vector>

namespace milk {

/// AST Node for an enum definition
/// A milk enum is simply a list of values
/// It is internally represented by an integer type
class ASTDefEnum : public AST {
public:
  using fields_t = std::vector<std::pair<std::string, int>>;

  /// @param beg_loc location of 'enum'
  /// @param end_loc location of ';'
  ASTDefEnum(const obcl::Location &beg_loc, const obcl::Location &end_loc,
             const std::string &name, ASTTypeLabelPtr &&type,
             const fields_t &fields)
      : AST(obcl::Location(beg_loc, end_loc)), _name(name),
        _type(std::move(type)), _fields(fields) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ASTTypeLabel &type() const { return *_type; }
  const fields_t &fields() const { return _fields; }

private:
  std::string _name;
  ASTTypeLabelPtr _type;
  fields_t _fields;
};

} // namespace milk
