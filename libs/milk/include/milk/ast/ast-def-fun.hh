//===--ast/ast-def-fun.hh - ASTDefFun class definition -----------*- C++-*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class ASTDefFun
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-stmt.hh"
#include "ast-visitor.hh"
#include "ast.hh"
#include <string>

namespace milk {

/// Represent a function definition in milk language, with its prototype and its
/// body
class ASTDefFun : public AST {
public:
  enum class Kind { FUN, METH, METH_CONST };

  /// @param beg_loc - location of 'fn'
  ASTDefFun(const obcl::Location &beg_loc, Kind kind, const std::string &name,
            ast_storage_list_t &&args, ASTTypeLabelPtr &&ret_type,
            ASTStmtPtr &&body)
      : AST(obcl::Location(beg_loc, body->loc())), _kind(kind), _name(name),
        _args(std::move(args)), _ret(std::move(ret_type)),
        _body(std::move(body)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  const std::string &name() const { return _name; }
  const ast_storage_list_t &args() const { return _args; }
  const ASTTypeLabel &ret_type() const { return *_ret; }
  const ASTStmt &body() const { return *_body; }

private:
  Kind _kind;
  std::string _name;
  ast_storage_list_t _args;
  ASTTypeLabelPtr _ret;
  ASTStmtPtr _body;
};

} // namespace milk
