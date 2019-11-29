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
#include "cgen/parser/parser.hh"
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

  void set_input_file(const std::string &input_file) {
    _input_file = input_file;
  }

private:
  using task_t = int;
  static constexpr task_t TASK_PARSE = 1;

  void _run_tasks(const std::vector<task_t> &tasks);
  void _run_task(task_t t);

  void _run_parse();

  std::string _input_file;
  std::unique_ptr<cgen::Parser> _parser;
  cgen::ASTProgram *_ast;

  std::set<task_t> _tasks_done;
  std::set<task_t> _tasks_todo;
};
