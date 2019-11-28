#include <cgen/ast/ast-visitor.hh>
#include <cgen/ast/all.hh>

namespace cgen
{

    void ASTVisitor::visit(const ASTDefFun& ast)
    {
        accept(ast.ret_type());
        for (const auto& arg: ast.args())
            accept(*arg.first);
        if (ast.has_body())
            accept(ast.body());
    }

    void ASTVisitor::visit(const ASTDefStruct& ast)
    {
        for (const auto& field: ast.fields())
            accept(*field.first);
    }

    void ASTVisitor::visit(const ASTDefType& ast)
    {
        accept(ast.type());
    }

    void ASTVisitor::visit(const ASTDefVar& ast)
    {
        accept(ast.type());
        if (ast.has_val())
            accept(ast.val());
    }

    void ASTVisitor::visit(const ASTExprBinOp& ast)
    {
        accept(ast.left());
        accept(ast.right());
    }

    void ASTVisitor::visit(const ASTExprCall& ast)
    {
        accept(ast.callee());
        for (const auto& arg : ast.args())
            accept(*arg);
    }

    void ASTVisitor::visit(const ASTExprCast& ast)
    {
        accept(ast.expr());
    }

    void ASTVisitor::visit(const ASTExprField& ast)
    {
        accept(ast.left());
    }

    void ASTVisitor::visit(const ASTExprFloat&)
    {

    }

    void ASTVisitor::visit(const ASTExprId&)
    {

    }

    void ASTVisitor::visit(const ASTExprInt&)
    {

    }

    void ASTVisitor::visit(const ASTExprSizeof& ast)
    {
        accept(ast.type());
    }

    void ASTVisitor::visit(const ASTExprString&)
    {

    }

    void ASTVisitor::visit(const ASTExprUnOp& ast)
    {
        accept(ast.right());
    }

    void ASTVisitor::visit(const ASTInstrBlock& ast)
    {
        for (const auto& ins : ast.instrs())
            accept(*ins);
    }

    void ASTVisitor::visit(const ASTInstrBreak&)
    {

    }

    void ASTVisitor::visit(const ASTInstrContinue&)
    {

    }

    void ASTVisitor::visit(const ASTInstrExpr& ast)
    {
        accept(ast.expr());
    }

    void ASTVisitor::visit(const ASTInstrIf& ast)
    {
        accept(ast.cond());
        accept(ast.instr_if());
        accept(ast.instr_else());
    }

    void ASTVisitor::visit(const ASTInstrReturn& ast)
    {
        if (ast.has_expr())
            accept(ast.val());
    }

    void ASTVisitor::visit(const ASTInstrVar& ast)
    {
        accept(ast.type());
    }

    void ASTVisitor::visit(const ASTInstrWhile& ast)
    {
        accept(ast.cond());
        accept(ast.body());
    }



    void ASTVisitor::visit(const ASTProgram& ast)
    {
        for (const auto& def : ast.defs())
            accept(*def);
    }

    void ASTVisitor::visit(const ASTTypeIdName&)
    {

    }

    void ASTVisitor::visit(const ASTTypeIdPointer& ast)
    {  
        accept(ast.type());
    }
    
}
