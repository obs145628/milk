//===--ast/ast-instr-while.hh - ASTInstrWhile class definition ---*-C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrWhile
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST node for a while instruction
class ASTInstrWhile : public ASTInstr {
public:
  /// @param beg_location location of 'while'
  ASTInstrWhile(const obcl::Location &beg_loc, ASTExprPtr &&cond,
                ASTInstrPtr &&body)
      : ASTInstr(obcl::Location(beg_loc, body->loc())), _cond(std::move(cond)),
        _body(std::move(body)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &cond() const { return *_cond; }
  const ASTInstr &body() const { return *_body; }

private:
  ASTExprPtr _cond;
  ASTInstrPtr _body;
};

} // namespace cgen
