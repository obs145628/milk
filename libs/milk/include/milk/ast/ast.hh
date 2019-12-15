//===--ast/ast.hh - AST class definition ------------------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class AST
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include "obcl/lexer/location.hh"

namespace milk {

/// Parent AST Class
/// All other AST classes herits from this one
/// Form a tree representation of the source code
class AST {
public:
  AST(const obcl::Location &loc) : _loc(loc) {}

  AST(const AST &) = delete;
  virtual ~AST() = default;

  virtual void accept(ASTVisitor &visitor) const = 0;

  /// @returns the complete location of the source code that generated this node
  const obcl::Location &loc() const { return _loc; }

private:
  obcl::Location _loc;
};
} // namespace milk
