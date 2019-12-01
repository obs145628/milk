//===--types/type-context.hh - TypeContext class definition --==-*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeContext
///
//===----------------------------------------------------------------------===//

#pragma once

#include "cgen/ast/ast-visitor.hh"
#include "cgen/ast/fwd.hh"
#include "fwd.hh"
#include "type.hh"
#include <map>
#include <vector>

namespace cgen {

// TODO: check if function return a value

/// AST Visitor for type informations
/// After creaaitng the AST, this visitor is applied to get and check semantic
/// infos
///
/// This class perform many tasks:
/// - register all struict and alias definitions
/// - register all function defninitions
/// - register all globable variable definitions
/// - register the local variables for every functions
/// - make sure functions returns, and returns the right type
/// - make sure all expression operations exists and use the right type
/// - bind break/continue to the correct loop
class TypeContext : public ASTVisitor {

  using scope_t = std::map<std::string, const Type *>;

  struct Fundef {
    std::string name;
    const TypeFun *type;
    scope_t scope;
  };

public:
  TypeContext();

  /// Called once on the AST to check and build the context
  /// Throw a TypeError is there is a semantic error in the source code
  void build(const ASTProgram &ast);

  /// Given a tpeid, get the actual real type
  const Type *type_of_typeid(const ASTTypeId &ast);

  /// Get the real type of an expression
  const Type *type_of_exp(const ASTExpr &ast);

  void visit(const ASTExprBinOp &ast) override;
  void visit(const ASTExprCall &ast) override;
  void visit(const ASTExprCast &ast) override;
  void visit(const ASTExprField &ast) override;
  void visit(const ASTExprFloat &ast) override;
  void visit(const ASTExprId &ast) override;
  void visit(const ASTExprInt &ast) override;
  void visit(const ASTExprSizeof &ast) override;
  void visit(const ASTExprString &ast) override;
  void visit(const ASTExprUnOp &ast) override;

  void visit(const ASTInstrBlock &ast) override;
  void visit(const ASTInstrBreak &ast) override;
  void visit(const ASTInstrContinue &ast) override;
  void visit(const ASTInstrExpr &ast) override;
  void visit(const ASTInstrIf &ast) override;
  void visit(const ASTInstrReturn &ast) override;
  void visit(const ASTInstrVar &ast) override;
  void visit(const ASTInstrWhile &ast) override;

  void visit(const ASTTypeIdName &ast) override;
  void visit(const ASTTypeIdPointer &ast) override;

private:
  /// function declarations
  std::map<std::string, Fundef> _fundefs;

  /// struct + aliases + native (int, float, void, ...)
  std::map<std::string, const Type *> _named_types;

  /// global variables
  std::map<std::string, const Type *> _globals;

  /// map Expr -> Type
  std::map<const ASTExpr *, const Type *> _type_exprs;
  const Type *_res_expr;

  /// map TypeId -> Type
  std::map<const ASTTypeId *, const Type *> _type_typeids;
  const Type *_res_typeid;

  ///@{
  /// map to assign loop to break / continue statements
  std::map<const ASTInstrBreak *, const ASTInstrWhile *> _loop_break;
  std::map<const ASTInstrContinue *, const ASTInstrWhile *> _loop_con;
  ///@}

  /// set to true when the visited instruction finished with a ret
  bool _ret_end;

  Fundef *_curr_fundef;
  const ASTInstrWhile *_curr_loop;

  void _add_native_defs();

  void _struct_decl(const ASTDefStruct &ast);
  void _struct_def(const ASTDefStruct &ast);
  void _global_decl(const ASTDefVar &ast);
  void _global_def(const ASTDefVar &ast);
  void _alias_def(const ASTDefType &ast);
  void _fun_decl(const ASTDefFun &ast);
  void _fun_def(const ASTDefFun &ast);

  /// check if \p act type can be replaced by \p expect
  /// throws a type mismatch error if couldn't
  /// TODO: check is really simple for now, do more complex
  static void _verify_type(const Type *expect, const Type *act, const AST &node,
                           const std::string &fn);

  /// verify all types for a binop
  /// throws a type mismatch
  static void _verify_binop(const Type *arg1, const Type *arg2, const Type *op1,
                            const Type *op2, const AST &node,
                            const std::string &fn);
};

} // namespace cgen
