//===--types/type-fun.hh - TypeFun class definition -------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeFun
///
//===----------------------------------------------------------------------===//

#pragma once

#include "type-visitor.hh"
#include "type.hh"
#include <vector>

namespace cgen {

/// cgen function type
/// Const of parameters type and return type
/// For now only used for function declarations and function call
class TypeFun : public Type {
  friend class TypeBuilder;

private:
  TypeFun(const Type *ret, const std::vector<const Type *> &args)
      : _ret(ret), _args(args) {}

public:
  std::string to_str() const override {
    auto res = _ret->to_str() + "(*)(";
    for (auto arg : _args)
      res += arg->to_str() + ", ";
    res += ")";
    return res;
  }

  void accept(TypeVisitor &v) const override { v.visit(*this); }

  const Type *ret() const { return _ret; }
  const std::vector<const Type *> args() const { return _args; }

private:
  const Type *_ret;
  std::vector<const Type *> _args;
};

} // namespace cgen
