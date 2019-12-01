#include "types/type-infos.hh"
#include "types/type-builder.hh"
#include "types/type-fun.hh"
#include "types/type-numeric.hh"
#include "types/type-ptr.hh"
#include "types/type-ref.hh"
#include "types/type-struct.hh"
#include "types/type-visitor.hh"

namespace cgen {

namespace {

class IsNumeric : public TypeVisitor {
public:
  bool run(const Type &t) {
    _res = false;
    accept(t);
    return _res;
  }

  void visit(const TypeU8 &) override { _res = true; }
  void visit(const TypeU16 &) override { _res = true; }
  void visit(const TypeU32 &) override { _res = true; }
  void visit(const TypeU64 &) override { _res = true; }
  void visit(const TypeI8 &) override { _res = true; }
  void visit(const TypeI16 &) override { _res = true; }
  void visit(const TypeI32 &) override { _res = true; }
  void visit(const TypeI64 &) override { _res = true; }
  void visit(const TypeF32 &) override { _res = true; }
  void visit(const TypeF64 &) override { _res = true; }

private:
  bool _res;
};

class GetSize : public TypeVisitor {
public:
  int run(const Type &t) {
    accept(t);
    return _res;
  }

  void visit(const TypeVoid &) override { _res = -1; }
  void visit(const TypeU8 &) override { _res = 1; }
  void visit(const TypeU16 &) override { _res = 2; }
  void visit(const TypeU32 &) override { _res = 4; }
  void visit(const TypeU64 &) override { _res = 8; }
  void visit(const TypeI8 &) override { _res = 1; }
  void visit(const TypeI16 &) override { _res = 2; }
  void visit(const TypeI32 &) override { _res = 4; }
  void visit(const TypeI64 &) override { _res = 8; }
  void visit(const TypeF32 &) override { _res = 4; }
  void visit(const TypeF64 &) override { _res = 8; }
  void visit(const TypeFun &) override { _res = sizeof(size_t); }
  void visit(const TypePtr &) override { _res = sizeof(size_t); }
  void visit(const TypeRef &t) override { accept(*t.type()); }
  void visit(const TypeStruct &) override { _res = -1; }

private:
  int _res;
};

} // namespace

namespace type_infos {

bool is_fun(const Type &t) {
  return dynamic_cast<const TypeFun *>(&t) != nullptr;
}

bool is_void(const Type &t) {
  return dynamic_cast<const TypeVoid *>(&t) != nullptr;
}

bool is_numeric(const Type &t) {
  IsNumeric isnum;
  return isnum.run(t);
}

bool is_int(const Type &t) { return is_numeric(t) && !is_float(t); }

bool is_float(const Type &t) {
  return dynamic_cast<const TypeF32 *>(&t) != nullptr ||
         dynamic_cast<const TypeF64 *>(&t) != nullptr;
}

bool is_ptr(const Type &t) {
  return dynamic_cast<const TypePtr *>(&t) != nullptr;
}

bool is_ref(const Type &t) {
  return dynamic_cast<const TypeRef *>(&t) != nullptr;
}

bool is_struct(const Type &t) {
  return dynamic_cast<const TypeStruct *>(&t) != nullptr;
}

const Type *type_bool() { return TypeBuilder::instance().i32(); }

const Type *type_char() { return TypeBuilder::instance().i8(); }

const Type *type_isize() { return TypeBuilder::instance().i64(); }

const Type *type_usize() { return TypeBuilder::instance().u64(); }

const Type *to_ref(const Type *t) {
  return is_ref(*t) ? t : TypeBuilder::instance().ref(t);
}

const Type *to_val(const Type *t) {
  auto tref = dynamic_cast<const TypeRef *>(t);
  return tref ? tref->type() : t;
}

int size(const Type *t) {
  GetSize v;
  return v.run(*t);
}

} // namespace type_infos

} // namespace cgen
