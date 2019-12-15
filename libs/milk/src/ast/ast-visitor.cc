#include "ast/ast-visitor.hh"
#include "ast/all.hh"

namespace milk {

/*
  void ASTVisitor::visit(const ASTDefFun& ast)
  {
      accept(ast.ret_type());
      for (const auto& arg: ast.args())
          accept(*arg.first);
      if (ast.has_body())
          accept(ast.body());
  }

*/

void ASTVisitor::visit(const ASTProgram &ast) {
  for (const auto &def : ast.defs())
    accept(*def);
}

void ASTVisitor::visit(const ASTTypeLabelName &) {}

void ASTVisitor::visit(const ASTTypeLabelRef &ast) { accept(ast.type()); }

} // namespace milk
