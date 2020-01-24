#include "type/type-visitor.hh"
#include "type/type-composite.hh"
#include "type/type-enum.hh"
#include "type/type-fun.hh"
#include "type/type-native.hh"
#include "type/type-ref.hh"
#include "type/type-struct.hh"
#include "type/type-void.hh"

namespace milk {

void TypeVisitor::visit(const TypeEnum &t) { accept(t.actual()); }

void TypeVisitor::visit(const TypeFun &t) {
  accept(t.ret());
  for (auto arg : t.args())
    accept(arg);
}

void TypeVisitor::visit(const TypeNativeFloat &) {}

void TypeVisitor::visit(const TypeNativeInt &) {}

void TypeVisitor::visit(const TypeRef &) {}

void TypeVisitor::visit(const TypeStruct &t) {
  if (t.is_defined())
    for (auto field : t.fields())
      accept(field.second);
}

void TypeVisitor::visit(const TypeVoid &) {}

} // namespace milk
