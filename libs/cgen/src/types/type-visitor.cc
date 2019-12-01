#include "types/type-visitor.hh"

namespace cgen {

void TypeVisitor::visit(const TypeFun &) {}

void TypeVisitor::visit(const TypeVoid &) {}

void TypeVisitor::visit(const TypeU8 &) {}

void TypeVisitor::visit(const TypeU16 &) {}

void TypeVisitor::visit(const TypeU32 &) {}

void TypeVisitor::visit(const TypeU64 &) {}

void TypeVisitor::visit(const TypeI8 &) {}

void TypeVisitor::visit(const TypeI16 &) {}

void TypeVisitor::visit(const TypeI32 &) {}

void TypeVisitor::visit(const TypeI64 &) {}

void TypeVisitor::visit(const TypeF32 &) {}

void TypeVisitor::visit(const TypeF64 &) {}

void TypeVisitor::visit(const TypePtr &) {}

void TypeVisitor::visit(const TypeRef &) {}

void TypeVisitor::visit(const TypeStruct &) {}

} // namespace cgen
