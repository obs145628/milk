#include "ast/ast-visitor.hh"
#include "ast/all.hh"

namespace milk {

void ASTVisitor::visit(const ASTDefAlias &ast) { accept(ast.type()); }

void ASTVisitor::visit(const ASTDefFun &ast) {
  for (const auto &arg : ast.args())
    accept(*arg.second);
  accept(ast.ret_type());
  accept(ast.body());
}

void ASTVisitor::visit(const ASTProgram &ast) {
  for (const auto &def : ast.defs())
    accept(*def);
}

void ASTVisitor::visit(const ASTNamedStorage &ast) { accept(ast.type()); }

void ASTVisitor::visit(const ASTTypeLabelName &) {}

void ASTVisitor::visit(const ASTTypeLabelRef &ast) { accept(ast.type()); }

} // namespace milk
