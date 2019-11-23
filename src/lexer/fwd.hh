//===-- lexer/fwd.hh - Forward definitions ----------------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the forward definition of alll structs/classes for the
/// lexer
/// And basic type aliases
///
//===----------------------------------------------------------------------===//

#pragma once

namespace obcl {

struct Location;
struct Position;
struct Token;
class Stream;

using token_type_t = int;

} // namespace obcl
