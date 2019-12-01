#include "types/type-builder.hh"
#include "types/type-fun.hh"
#include "types/type-numeric.hh"
#include "types/type-ptr.hh"
#include "types/type-ref.hh"
#include "types/type-struct.hh"

#include <cassert>

namespace cgen {

TypeBuilder &TypeBuilder::instance() {
  static TypeBuilder res;
  return res;
}

std::string TypeBuilder::id_void() { return "n:void"; }

std::string TypeBuilder::id_u8() { return "n:u8"; }

std::string TypeBuilder::id_u16() { return "n:u16"; }

std::string TypeBuilder::id_u32() { return "n:u32"; }

std::string TypeBuilder::id_u64() { return "n:u64"; }

std::string TypeBuilder::id_i8() { return "n:i8"; }

std::string TypeBuilder::id_i16() { return "n:i16"; }

std::string TypeBuilder::id_i32() { return "n:i32"; }

std::string TypeBuilder::id_i64() { return "n:i64"; }

std::string TypeBuilder::id_f32() { return "n:f32"; }

std::string TypeBuilder::id_f64() { return "n:f64"; }

std::string TypeBuilder::id_fun(const Type *ret,
                                const std::vector<const Type *> &args) {
  std::string id = "f<";
  for (std::size_t i = 0; i < args.size(); ++i) {
    id += id_of(args[i]);
    if (i + 1 < args.size())
      id += ",";
  }
  id += "|" + id_of(ret) + ">";

  return id;
}

std::string TypeBuilder::id_ptr(const Type *type) {
  return "p<" + id_of(type) + ">";
}

std::string TypeBuilder::id_ref(const Type *type) {
  return "r<" + id_of(type) + ">";
}

std::string TypeBuilder::id_struct(const std::string &name) {
  return "s:" + name;
}

const std::string &TypeBuilder::id_of(const Type *type) const {
  auto it = _ids_map.find(type);
  assert(it != _ids_map.end());
  return it->second;
}

const Type *TypeBuilder::type_void() {
  auto id = id_void();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeVoid());
}

const Type *TypeBuilder::u8() {
  auto id = id_u8();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeU8());
}

const Type *TypeBuilder::u16() {
  auto id = id_u16();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeU16());
}

const Type *TypeBuilder::u32() {
  auto id = id_u32();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeU32());
}

const Type *TypeBuilder::u64() {
  auto id = id_u64();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeU64());
}

const Type *TypeBuilder::i8() {
  auto id = id_i8();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeI8());
}

const Type *TypeBuilder::i16() {
  auto id = id_i16();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeI16());
}

const Type *TypeBuilder::i32() {
  auto id = id_i32();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeI32());
}

const Type *TypeBuilder::i64() {
  auto id = id_i64();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeI64());
}

const Type *TypeBuilder::f32() {
  auto id = id_f32();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeF32());
}

const Type *TypeBuilder::f64() {
  auto id = id_f64();
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeF64());
}

const Type *TypeBuilder::fun(const Type *ret,
                             const std::vector<const Type *> &args) {
  auto id = id_fun(ret, args);
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeFun(ret, args));
}

const Type *TypeBuilder::ptr(const Type *type) {
  auto id = id_ptr(type);
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypePtr(type));
}

const Type *TypeBuilder::ref(const Type *type) {
  auto id = id_ref(type);
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeRef(type));
}

const Type *TypeBuilder::type_struct(const std::string &name) {
  auto id = id_struct(name);
  auto it = _types.find(id);
  if (it != _types.end())
    return it->second;

  return _add_type(id, new TypeStruct(name));
}

const Type *TypeBuilder::_add_type(const std::string &id, Type *raw_ptr) {
  _defs.emplace_back(raw_ptr);
  _types.emplace(id, raw_ptr);
  _ids_map.emplace(raw_ptr, id);
  return raw_ptr;
}

} // namespace cgen
