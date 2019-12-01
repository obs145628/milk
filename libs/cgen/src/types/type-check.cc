#include "types/type-check.hh"
#include "types/type-infos.hh"
#include "types/type-numeric.hh"
#include "types/type-ptr.hh"
#include "types/type-ref.hh"
#include "types/type-struct.hh"
#include "types/type-visitor.hh"
#include "types/type.hh"

#include <iostream>

namespace cgen {
namespace type_check {

bool match(const Type *exp, const Type *act) {
  auto rexp = dynamic_cast<const TypeRef *>(exp);
  auto ract = dynamic_cast<const TypeRef *>(act);
  if (rexp && !ract)
    return false;
  exp = rexp ? rexp->type() : exp;
  act = ract ? ract->type() : act;

  return equals(exp, act);
}

bool equals(const Type *t1, const Type *t2) { return t1 == t2; }

} // namespace type_check

} // namespace cgen
