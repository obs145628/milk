//===--compiler/compiler.hh - Compiler class definition ---------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the class Compiler
///
//===----------------------------------------------------------------------===//

#pragma once

#include <string>

namespace milk {

/// Perform all needed steps for compilation
/// Big utils class to handle compil options, generate intermediate or binary
/// files
class Compiler {
public:
  Compiler();
  Compiler(const Compiler &) = delete;
  Compiler &operator=(const Compiler &) = delete;

  void parse_file(const std::string &path);

private:
};

} // namespace milk
