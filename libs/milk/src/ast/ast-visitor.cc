#include "ast/ast-visitor.hh"
#include "ast/all.hh"

namespace milk {

void ASTVisitor::visit(const ASTDefAlias &ast) { accept(ast.type()); }

void ASTVisitor::visit(const ASTDefEnum &ast) { accept(ast.type()); }

void ASTVisitor::visit(const ASTDefFun &ast) {
  for (const auto &arg : ast.args())
    accept(*arg);
  accept(ast.ret_type());
  accept(ast.body());
}

void ASTVisitor::visit(const ASTDefStruct &ast) {
  for (const auto &field : ast.fields())
    accept(*field);
}

void ASTVisitor::visit(const ASTDefVar &ast) { accept(ast.storage()); }

void ASTVisitor::visit(const ASTNamedStorage &ast) { accept(ast.type()); }

void ASTVisitor::visit(const ASTProgram &ast) {
  for (const auto &def : ast.defs())
    accept(*def);
}

void ASTVisitor::visit(const ASTStmtBlock &ast) {
  for (const auto &st : ast.stmts())
    accept(*st);
}

void ASTVisitor::visit(const ASTStmtExpr &ast) { accept(ast.expr()); }

void ASTVisitor::visit(const ASTStmtIf &ast) {
  accept(ast.cond());
  accept(ast.if_stmt());
  accept(ast.else_stmt());
}

void ASTVisitor::visit(const ASTStmtVar &ast) {
  accept(ast.storage());
  accept(ast.init());
}

void ASTVisitor::visit(const ASTTypeLabelName &) {}

void ASTVisitor::visit(const ASTTypeLabelRef &ast) { accept(ast.type()); }

} // namespace milk
