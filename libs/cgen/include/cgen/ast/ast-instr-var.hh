//===--ast/ast-instr-var.hh - ASTInstrVar class definition --------*-C++-*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrVar
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"
#include <string>

namespace cgen {

/// AST Node to define local variable
/// No initializer
/// [TODO] Should be removed
class ASTInstrVar : public ASTInstr {
public:
  /// @param beg_loc location of 'var'
  /// @param end_loc location of ';'
  /// @param name variable identifier name
  /// @param type - variable typename
  ASTInstrVar(const obcl::Location &beg_loc, const obcl::Location &end_loc,
              const std::string &name, ASTTypeIdPtr &&type)
      : ASTInstr(obcl::Location(beg_loc, end_loc)), _name(name),
        _type(std::move(type)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ASTTypeId &type() const { return *_type; }

private:
  std::string _name;
  ASTTypeIdPtr _type;
};

} // namespace cgen
