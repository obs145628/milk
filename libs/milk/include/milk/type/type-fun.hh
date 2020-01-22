//===--type/type-fun.hh - TypeFun class definition --------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class TypeFun
///
//===----------------------------------------------------------------------===//

#pragma once

#include <vector>

#include "fwd.hh"
#include "type-composite.hh"
#include "type-visitor.hh"

namespace milk {

/// Class to represent a function type
class TypeFun : public TypeComposite {
public:
  TypeFun(const Type *ret, const std::vector<const Type *> &args)
      : _ret(ret), _args(args) {}

  const Type *ret() const { return _ret; }
  const std::vector<const Type *> &args() const { return _args; }

  void accept(TypeVisitor &visitor) const override { visitor.visit(*this); }

private:
  const Type *_ret;
  std::vector<const Type *> _args;
};
} // namespace milk
