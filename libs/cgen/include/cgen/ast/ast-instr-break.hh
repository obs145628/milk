//===--ast/ast-instr-break.hh - ASTInstrBreak class definition ---*-C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrBreak
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST Node for the break instruction
class ASTInstrBreak : public ASTInstr {
public:
  /// @param beg_log location of 'break'
  /// @param end_loc location of ';'
  ASTInstrBreak(const obcl::Location &beg_loc, const obcl::Location &end_loc)
      : ASTInstr(obcl::Location(beg_loc, end_loc)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

private:
};

} // namespace cgen
