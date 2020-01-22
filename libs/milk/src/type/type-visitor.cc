#include "type/type-visitor.hh"
#include "type/type-composite.hh"
#include "type/type-fun.hh"
#include "type/type-simple.hh"
#include "type/type-val.hh"

namespace milk {

void TypeVisitor::visit(const TypeFun &t) {
  accept(t.ret());
  for (auto arg : t.args())
    accept(arg);
}

} // namespace milk
