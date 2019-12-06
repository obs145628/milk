//===-- bincl/compiler.hh - Compiler class definition ----=----*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the definition of the Compiler class
///
//===----------------------------------------------------------------------===//

#pragma once

#include <string>
#include <vector>

namespace obcl {

namespace bin {

/// Run C/C++ compiler binary program
/// Used to run gcc / g++ / clang / etc
class Compiler {
public:
  enum class DebugMode { NO, L1, L2, L3 };

  Compiler();

  void build_object(const std::string &in_src, const std::string &out_obj);

  void build_bin(const std::vector<std::string> &in_src,
                 const std::string &out_bin);

  void set_debug(DebugMode mode) { _debug = mode; }

  /// Change the path to the binary compiler program
  void set_bin_path(const std::string &path) { _bin_path = path; }

  /// Add a static / dynamic library
  /// Right now, only works for static libraries
  /// [TODO] Add support for dynamic libraries
  void add_lib(const std::string &path);

private:
  std::string _bin_path;
  std::vector<std::string> _static_libs;
  DebugMode _debug;

  void _add_cl_options(std::vector<std::string> &args) const;
  void _run_cl(const std::vector<std::string> &args) const;
};

} // namespace bin

} // namespace obcl
