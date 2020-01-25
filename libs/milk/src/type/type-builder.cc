#include "type/type-builder.hh"

#include <cassert>

#include "type/type-codes.hh"
#include "type/type-enum.hh"
#include "type/type-fun.hh"
#include "type/type-native.hh"
#include "type/type-ref.hh"
#include "type/type-struct.hh"
#include "type/type-void.hh"

#define NATIVE_BUILDER(Code, Classname)                                        \
  auto it = _val_types.find(typecode::CODE_##Code);                            \
  if (it != _val_types.end()) {                                                \
    auto res = dynamic_cast<const Classname *>(it->second);                    \
    assert(res && res->kind() == Classname::Kind::Code);                       \
    return res;                                                                \
  }                                                                            \
                                                                               \
  auto res = new Classname(Classname::Kind::Code);                             \
  _val_types.emplace(typecode::CODE_##Code, res);                              \
  return res;

namespace milk {

TypeBuilder::TypeBuilder() : _enum_count(0), _struct_count(0) {}

const TypeVoid *TypeBuilder::type_void() {
  auto it = _val_types.find(typecode::CODE_VOID);
  if (it != _val_types.end()) {
    auto res = dynamic_cast<const TypeVoid *>(it->second);
    assert(res);
    return res;
  }

  auto res = new TypeVoid();
  _val_types.emplace(typecode::CODE_VOID, res);
  return res;
}

const TypeNativeInt *TypeBuilder::type_u8() {
  NATIVE_BUILDER(U8, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_u16() {
  NATIVE_BUILDER(U16, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_u32() {
  NATIVE_BUILDER(U32, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_u64() {
  NATIVE_BUILDER(U64, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_i8() {
  NATIVE_BUILDER(I8, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_i16() {
  NATIVE_BUILDER(I16, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_i32() {
  NATIVE_BUILDER(I32, TypeNativeInt)
}

const TypeNativeInt *TypeBuilder::type_i64() {
  NATIVE_BUILDER(I64, TypeNativeInt)
}

const TypeNativeFloat *TypeBuilder::type_f32() {
  NATIVE_BUILDER(F32, TypeNativeFloat)
}

const TypeNativeFloat *TypeBuilder::type_f64() {
  NATIVE_BUILDER(F64, TypeNativeFloat)
}

const TypeVal *TypeBuilder::type_val(const TypeRef *ty) {
  assert(ty->_type_val);
  return ty->_type_val;
}

const TypeRef *TypeBuilder::type_mref(const TypeVal *ty) {
  if (!ty->_type_mref)
    ty->_type_mref = new TypeRef(ty, TypeRef::Kind::MREF);
  return ty->_type_mref;
}

const TypeRef *TypeBuilder::type_cref(const TypeVal *ty) {
  if (!ty->_type_cref)
    ty->_type_cref = new TypeRef(ty, TypeRef::Kind::CREF);
  return ty->_type_cref;
}

const TypeRef *TypeBuilder::type_amref(const TypeVal *ty) {
  if (!ty->_type_amref)
    ty->_type_amref = new TypeRef(ty, TypeRef::Kind::AMREF);
  return ty->_type_amref;
}

const TypeRef *TypeBuilder::type_acref(const TypeVal *ty) {
  if (!ty->_type_acref)
    ty->_type_acref = new TypeRef(ty, TypeRef::Kind::ACREF);
  return ty->_type_acref;
}

const TypeFun *TypeBuilder::type_fun(const Type *ret,
                                     const std::vector<const Type *> &args) {
  // TODO: still requires 1 vector allocation to check if fun already defined,
  // how to avoid this ?
  TypeFun mock_fun(ret, args);
  auto it = _funs_table.find(&mock_fun);
  if (it != _funs_table.end())
    return *it;

  auto res = new TypeFun(ret, args);
  _funs_table.insert(res);
  return res;
}

const TypeStruct *TypeBuilder::make_type_struct(const std::string &name) {
  auto code = typecode::CODE_START_STRUCT + ++_struct_count;
  auto res = new TypeStruct(code, name);
  return res;
}

const TypeEnum *
TypeBuilder::make_type_enum(const std::string &name,
                            const TypeNativeInt *actual,
                            const std::map<std::string, int> &fields) {
  auto code = typecode::CODE_START_ENUM + ++_enum_count;
  auto res = new TypeEnum(code, name, actual, fields);
  return res;
}

std::size_t TypeBuilder::TypeFunHash::operator()(const TypeFun *ty) const
    noexcept {
  std::size_t res = 0;

  auto ret_simple = dynamic_cast<const TypeSimple *>(ty->ret());
  assert(ret_simple);
  res ^= std::hash<const TypeSimple *>()(ret_simple);

  for (auto arg : ty->args()) {
    auto arg_simple = dynamic_cast<const TypeSimple *>(arg);
    assert(arg_simple);
    res ^= std::hash<const TypeSimple *>()(arg_simple);
  }

  return res;
}

bool TypeBuilder::TypeFunEq::operator()(const TypeFun *a,
                                        const TypeFun *b) const noexcept {
  return a->ret() == b->ret() && a->args() == b->args();
}

} // namespace milk
