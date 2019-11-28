//===--ast/ast-expr-call.hh - ASTExprCall class definition -------*- C++-*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprCall
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"

namespace cgen {

/// AST Node that representat a function call
class ASTExprCall : public ASTExpr {

public:
  ///
  /// @param end_loc location of the last token of the parsed node
  /// @param callee - called expr (function identifier or other)
  /// @param args - list of args expressions
  ASTExprCall(const obcl::Location &end_loc, ASTExprPtr &&callee,
              ast_exprs_list_t &&args)
      : ASTExpr(obcl::Location(callee->loc(), end_loc)),
        _callee(std::move(callee)), _args(std::move(args)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const ASTExpr &callee() const { return *_callee; }
  const ast_exprs_list_t &args() const { return _args; }

private:
  ASTExprPtr _callee;
  ast_exprs_list_t _args;
};

} // namespace cgen
