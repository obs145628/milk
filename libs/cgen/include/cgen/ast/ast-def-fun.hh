//===--ast/ast-def-fun.hh - ASTDefFun class definition ----------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTDefFun
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def.hh"
#include "ast-instr.hh"
#include "ast-visitor.hh"
#include "fwd.hh"
#include <string>
#include <utility>
#include <vector>

namespace cgen {

/// AST Node to delare a cgen function
/// Can be just an extern declaration, or also a definition with the funciton
/// body
class ASTDefFun : public ASTDef {
public:
  ///
  /// @param beg_loc location of the first token of the parsed function
  /// @param end_loc location of the last token of the parsed function
  /// @paran name function identifier name
  /// @param ret_type AST Node for the return type
  /// @param args list of AST nodes for the arguments
  /// @param body function body, nullptr if this is an extern declaration
  ASTDefFun(const obcl::Location &beg_loc, const obcl::Location &end_loc,
            const std::string &name, ASTTypeIdPtr &&ret_type,
            ast_args_def_t &&args, ASTInstrPtr &&body)
      : ASTDef(obcl::Location(beg_loc, end_loc)), _name(name),
        _ret_type(std::move(ret_type)), _args(std::move(args)),
        _body(std::move(body)) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &name() const { return _name; }
  const ASTTypeId &ret_type() const { return *_ret_type; }
  const ast_args_def_t &args() const { return _args; }
  const ASTInstr &body() const { return *_body; }
  bool has_body() const { return _body.get(); }

private:
  std::string _name;
  ASTTypeIdPtr _ret_type;
  ast_args_def_t _args;
  ASTInstrPtr _body;
};

} // namespace cgen
