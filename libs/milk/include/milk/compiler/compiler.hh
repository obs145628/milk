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

  /// If /p use_custom is true, when a compiler error happens, a specific error
  /// code is returned depending on the error kind. Otherwhise, all errors
  /// returns with error 1
  void set_custom_ret_code(bool use_custom) { _custom_ret_code = use_custom; }

private:
  bool _custom_ret_code;

  void _compile_error(const std::exception &e, int code);
};

} // namespace milk
