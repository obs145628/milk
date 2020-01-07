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

#include "ast-def.hh"
#include "ast-stmt.hh"
#include "ast-visitor.hh"
#include <string>

namespace milk {

/// Represent a function definition in milk language, with its prototype and its
/// body
class ASTDefFun : public ASTDef {
public:
  enum class Kind { FUN, METH };
  enum class ImplKind { CODE, DEFAULT };

  ASTDefFun(const obcl::Location &loc, Kind kind, ImplKind impl_kind,
            bool is_const, bool is_static, const std::string &name,
            ast_storage_list_t &&args, ASTTypeLabelPtr &&ret_type,
            ASTStmtPtr &&body)
      : ASTDef(loc), _kind(kind), _impl_kind(impl_kind), _is_const(is_const),
        _is_static(is_static), _name(name), _args(std::move(args)),
        _ret(std::move(ret_type)), _body(std::move(body)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  Kind kind() const { return _kind; }
  ImplKind impl_kind() const { return _impl_kind; }
  bool is_const() const { return _is_const; }
  bool is_static() const { return _is_static; }

  const std::string &name() const { return _name; }
  const ast_storage_list_t &args() const { return _args; }
  const ASTTypeLabel &ret_type() const { return *_ret; }
  bool has_body() const { return _body.get(); }
  const ASTStmt &body() const { return *_body; }

private:
  Kind _kind;
  ImplKind _impl_kind;
  bool _is_const;
  bool _is_static;
  std::string _name;
  ast_storage_list_t _args;
  ASTTypeLabelPtr _ret;
  ASTStmtPtr _body;
};

} // namespace milk
