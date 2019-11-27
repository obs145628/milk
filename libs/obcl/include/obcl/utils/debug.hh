//===-- lexer/stream.hh - Lexer class definition ----------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of several tools for Debugging
/// It displays informations relative to the program internals
///
//===----------------------------------------------------------------------===//

#include <string>

namespace obcl {

/// helper function, use PANIC(str) maccro instead
void panic_fn(const char *file, int line, const char *fun,
              const std::string &msg);

} // namespace obcl

#define PANIC(X) (panic_fn(__FILE__, __LINE__, __func__, X))
