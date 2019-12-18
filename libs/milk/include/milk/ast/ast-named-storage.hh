//===--ast/ast-named-storage.hh - ASTNamedStorage class ----------- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTNamedstorage
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-visitor.hh"
#include "ast.hh"
#include <string>

namespace milk {

/// AST Node to represent an entity in the language, with storage capabilities
/// (read from / write to memory) It is used for:
/// - local variable declaration
/// - funciton argument
/// - struct attribute
class ASTNamedStorage : public AST {
public:
  ASTNamedStorage(const obcl::Location &loc, const std::string &name,
                  bool is_const, ASTTypeLabelPtr &&type)
      : AST(loc), _name(name), _const(is_const), _type(std::move(type)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  bool is_const() const { return _const; }
  bool has_type() const { return _type.get() != nullptr; }
  const ASTTypeLabel &type() const { return *_type; }

private:
  std::string _name;
  bool _const;
  ASTTypeLabelPtr _type;
};

} // namespace milk
