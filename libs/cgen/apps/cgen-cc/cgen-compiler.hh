//===--cgen-compiler.hh - CGenCompiler class definition ---------*- C++ -*-===//
//
// cgen-cc program
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class CGencompiler
///
//===----------------------------------------------------------------------===//

#pragma once

#include "cgen/ast/all.hh"
#include "cgen/ctranslator/ctranslator.hh"
#include "cgen/parser/parser.hh"
#include "cgen/types/type-context.hh"
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

/// Class to handle the whole cgen to C compiler
/// Can do any step of the compilation
/// To binary geenration
class CGenCompiler {
public:
  CGenCompiler();
  CGenCompiler(const CGenCompiler &) = delete;
  CGenCompiler &operator=(const CGenCompiler &) = delete;

  /// Run all the requested operations
  /// Exit if something failed
  void run();

  /// Enable the parsing task
  void do_parse();

  /// Enable the semantic analysis task
  void do_type();

  /// Enablke the c translation task
  void do_ctranslate();

  /// Enable the build object file (.o) task
  void do_build_object();

  /// Enable the build binary task
  void do_build_binary();

  void add_input_file(const std::string &input_file) {
    _input_files.push_back(input_file);
  }

  /// Output file when writing to C
  /// If not set, name is first-input-file.c (in current directory)
  /// If '-', output on stdout
  void set_output_c_file(const std::string &path) { _output_c_file = path; }

  /// Output object file
  /// If not set, name is first-input-file.o (in current directory)
  void set_output_object_file(const std::string &path) {
    _output_object_file = path;
  }

  /// Output binary file
  /// If not set, name is first-input-file.out (in current directory)
  void set_output_binary_file(const std::string &path) {
    _output_binary_file = path;
  }

  /// If \p opt is true, enable debug flags when compiling c flags
  /// The debug locations are linked to the generated c file, not the original
  /// source code
  void set_cc_debug(bool opt) { _cc_debug = opt; }

  /// If \p ret_code is true, the program will exit with a specific error code
  /// when an error happens, depending on the error king (otherwhise, always
  /// exit with 1)
  void set_custom_ret_code(bool ret_code) { _custom_ret_code = ret_code; }

  /// Add a compiled static / shared library to be linked when building a
  /// binary file
  void add_c_lib(const std::string &path) { _c_libs.push_back(path); }

private:
  using task_t = int;
  static constexpr task_t TASK_PARSE = 1;
  static constexpr task_t TASK_TYPE = 2;
  static constexpr task_t TASK_CTRANSLATE = 3;
  static constexpr task_t TASK_BUILD_OBJECT = 4;
  static constexpr task_t TASK_BUILD_BINARY = 5;

  /// @param is_tmp - If true, all output files build during any of \p tasks are
  /// temporary files, not needed after compilation
  void _run_tasks(const std::vector<task_t> &tasks, bool is_tmp = false);

  void _run_task(task_t t);
  void _run_parse();
  void _run_type();
  void _run_ctranslate();
  void _run_build_object();
  void _run_build_binary();

  /// @returns a default otput path, based on the \p input name, if building an
  /// output file otherwhise a temporary path for temporary file
  std::string _get_tmp_or_dft_path(const std::string &input,
                                   const std::string &ext);

  std::string _get_tmp_path(const std::string &suffix);

  void _compile_error(const std::exception &e, int code);

  std::vector<std::string> _input_files;
  std::vector<std::string> _c_libs;
  std::string _output_c_file;
  std::string _output_object_file;
  std::string _output_binary_file;
  std::unique_ptr<cgen::Parser> _parser;
  std::unique_ptr<cgen::TypeContext> _type_ctx;
  std::unique_ptr<cgen::CTranslator> _ctrans;
  cgen::ASTProgram *_ast;
  bool _build_tmp;

  bool _cc_debug;
  bool _custom_ret_code;

  std::set<task_t> _tasks_done;
  std::set<task_t> _tasks_todo;
};
