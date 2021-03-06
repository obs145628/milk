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

void ASTVisitor::visit(const ASTExprCall &ast) {
  accept(ast.callee());
  for (const auto &arg : ast.args())
    accept(*arg);
}

void ASTVisitor::visit(const ASTExprCallNamed &ast) {
  accept(ast.callee());
  for (const auto &arg : ast.args())
    accept(*arg.second);
}

void ASTVisitor::visit(const ASTExprField &ast) { accept(ast.val()); }

void ASTVisitor::visit(const ASTExprId &) {}

void ASTVisitor::visit(const ASTExprNumber &) {}

void ASTVisitor::visit(const ASTExprSpecial &ast) {
  for (const auto &op : ast.operands())
    accept(*op);
}

void ASTVisitor::visit(const ASTNamedStorage &ast) {
  if (ast.has_type())
    accept(ast.type());
}

void ASTVisitor::visit(const ASTProgram &ast) {
  for (const auto &def : ast.defs())
    accept(*def);
}

void ASTVisitor::visit(const ASTStmtBlock &ast) {
  for (const auto &st : ast.stmts())
    accept(*st);
}

void ASTVisitor::visit(const ASTStmtBreak &) {}

void ASTVisitor::visit(const ASTStmtExpr &ast) { accept(ast.expr()); }

void ASTVisitor::visit(const ASTStmtIf &ast) {
  accept(ast.cond());
  accept(ast.if_stmt());
  accept(ast.else_stmt());
}

void ASTVisitor::visit(const ASTStmtReturn &ast) {
  if (ast.has_val())
    accept(ast.val());
}

void ASTVisitor::visit(const ASTStmtVar &ast) {
  accept(ast.storage());
  accept(ast.init());
}

void ASTVisitor::visit(const ASTStmtWhile &ast) {
  accept(ast.cond());
  accept(ast.body());
}

void ASTVisitor::visit(const ASTTypeLabelName &) {}

void ASTVisitor::visit(const ASTTypeLabelRef &ast) { accept(ast.type()); }

} // namespace milk
