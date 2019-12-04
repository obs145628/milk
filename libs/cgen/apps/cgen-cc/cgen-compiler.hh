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

  void add_input_file(const std::string &input_file) {
    _input_files.push_back(input_file);
  }

  /// Output file when writing to C
  /// If not set, name is first-input-file.c (in current directory)
  /// If '-', output on stdout
  void set_output_c_file(const std::string &path) { _output_c_file = path; }

private:
  using task_t = int;
  static constexpr task_t TASK_PARSE = 1;
  static constexpr task_t TASK_TYPE = 2;
  static constexpr task_t TASK_CTRANSLATE = 3;

  void _run_tasks(const std::vector<task_t> &tasks);
  void _run_task(task_t t);

  void _run_parse();
  void _run_type();
  void _run_ctranslate();

  std::vector<std::string> _input_files;
  std::string _output_c_file;
  std::unique_ptr<cgen::Parser> _parser;
  std::unique_ptr<cgen::TypeContext> _type_ctx;
  std::unique_ptr<cgen::CTranslator> _ctrans;
  cgen::ASTProgram *_ast;

  std::set<task_t> _tasks_done;
  std::set<task_t> _tasks_todo;
};
