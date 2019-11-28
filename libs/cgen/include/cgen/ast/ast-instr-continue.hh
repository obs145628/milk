//===--ast/ast-instr-continue.hh - ASTInstrContinue class --------*-C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrContinue
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST Node for instruction continue
class ASTInstrContinue : public ASTInstr {
public:
  /// @param beg_log location of 'continue'
  /// @param end_loc location of ';'
  ASTInstrContinue(const obcl::Location &beg_loc, const obcl::Location &end_loc)
      : ASTInstr(obcl::Location(beg_loc, end_loc)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

private:
};

} // namespace cgen
