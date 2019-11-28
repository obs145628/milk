//===--ast/ast-instr-return.hh - ASTInstrReturn class definition -*-C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrReturn
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST node for return instruction
/// The return value is optinal (omitted for void functions)
class ASTInstrReturn : public ASTInstr {
public:
  /// @param beg_loc location of 'return'
  /// @param end_loc location of ';'
  /// @param val return value, can be nullptr
  ASTInstrReturn(const obcl::Location &beg_loc, const obcl::Location &end_loc,
                 ASTExprPtr &&val)
      : ASTInstr(obcl::Location(beg_loc, end_loc)), _val(std::move(val)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  bool has_expr() const { return _val.get(); }
  const ASTExpr &val() const { return *_val; }

private:
  ASTExprPtr _val;
};

} // namespace cgen
