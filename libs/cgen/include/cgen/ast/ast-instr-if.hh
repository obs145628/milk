//===--ast/ast-instr-if.hh - ASTInstrIf class definition ----------*-C++-*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrIf
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST Node for if/else instruction
/// else is required, but can be empty block
class ASTInstrIf : public ASTInstr {
public:
  /// @param beg_log location of 'if'
  /// @param cond condition expression
  /// @param inst_if instruction executed if condition is true
  /// @param instr_else instruction executed if condition is false
  ASTInstrIf(const obcl::Location &beg_loc, ASTExprPtr &&cond,
             ASTInstrPtr &&instr_if, ASTInstrPtr &&instr_else)
      : ASTInstr(obcl::Location(beg_loc, instr_else->loc())),
        _cond(std::move(cond)), _instr_if(std::move(instr_if)),
        _instr_else(std::move(instr_else)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &cond() const { return *_cond; }
  const ASTInstr &instr_if() const { return *_instr_if; }
  const ASTInstr &instr_else() const { return *_instr_else; }

private:
  ASTExprPtr _cond;
  ASTInstrPtr _instr_if;
  ASTInstrPtr _instr_else;
};

} // namespace cgen
