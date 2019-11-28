//===--ast/ast-program.hh - ASTProgram class definition ---------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTProgram
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-visitor.hh"
#include "ast.hh"
#include "fwd.hh"
#include <algorithm>
#include <vector>

namespace cgen {

/// Root class of an AST
/// There is one ASTProgram for the whole compilation
/// Contains a list of definitions (struct, functions, globals, etc)
class ASTProgram : public AST {
public:
  ASTProgram(std::vector<ASTDefPtr> &&defs)
      : AST(obcl::Location(obcl::Location::begin_of(defs),
                           obcl::Location::end_of(defs))),
        _defs(std::move(defs)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::vector<ASTDefPtr> &defs() const { return _defs; }

  void extend(ASTProgramPtr &&src) {
    auto src_defs = std::move(src->_defs);
    std::move(src_defs.begin(), src_defs.end(), std::back_inserter(_defs));
  }

private:
  std::vector<ASTDefPtr> _defs;
};

} // namespace cgen
