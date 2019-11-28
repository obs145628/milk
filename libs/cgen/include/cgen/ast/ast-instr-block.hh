//===--ast/ast-instr-block.hh - ASTInstrBlock class definition ----*-C++
//-*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTInstrBlock
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"

namespace cgen {

/// AST Node for a group of instructions
/// (There is no scope)
class ASTInstrBlock : public ASTInstr {
public:
  ///
  /// @param beg_loc location of the first token of the parsed node
  /// @param end_loc location of the last token of the parsed node
  /// @param instrs list of instructions
  ASTInstrBlock(const obcl::Location &beg_loc, const obcl::Location &end_loc,
                ast_instrs_list_t &&instrs)
      : ASTInstr(obcl::Location(beg_loc, end_loc)), _instrs(std::move(instrs)) {
  }

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ast_instrs_list_t &instrs() const { return _instrs; }

  static ASTInstrBlockPtr empty(const obcl::Location &loc) {
    return std::make_unique<ASTInstrBlock>(loc, loc, ast_instrs_list_t{});
  }

private:
  ast_instrs_list_t _instrs;
};

} // namespace cgen
