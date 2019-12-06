#include "cgen-compiler.hh"
#include "cgen/types/type-error.hh"
#include "obcl/bincl/compiler.hh"
#include "obcl/lexer/lexer-error.hh"
#include "obcl/parser/parser-error.hh"
#include "obcl/utils/debug.hh"
#include "obcl/utils/path.hh"
#include <cstdlib>
#include <fstream>
#include <iostream>

CGenCompiler::CGenCompiler() : _ast(nullptr), _build_tmp(false) {}

namespace {

void compile_error(const std::exception &e) {
  std::cerr << "Compilation failed: " << std::endl << e.what();
  std::exit(1);
}
} // namespace

void CGenCompiler::run() {
  for (const auto &t : _tasks_todo)
    _run_task(t);
}

void CGenCompiler::do_parse() { _tasks_todo.insert(TASK_PARSE); }

void CGenCompiler::do_type() { _tasks_todo.insert(TASK_TYPE); }

void CGenCompiler::do_ctranslate() { _tasks_todo.insert(TASK_CTRANSLATE); }

void CGenCompiler::do_build_object() { _tasks_todo.insert(TASK_BUILD_OBJECT); }

void CGenCompiler::do_build_binary() { _tasks_todo.insert(TASK_BUILD_BINARY); }

void CGenCompiler::_run_tasks(const std::vector<task_t> &tasks, bool is_tmp) {
  bool old_tmp = _build_tmp;
  _build_tmp = is_tmp;
  for (const auto &t : tasks)
    _run_task(t);
  _build_tmp = old_tmp;
}

void CGenCompiler::_run_task(task_t t) {
  if (_tasks_done.find(t) != _tasks_done.end())
    return;

  switch (t) {
  case TASK_PARSE:
    _run_parse();
    break;

  case TASK_TYPE:
    _run_tasks({TASK_PARSE});
    _run_type();
    break;

  case TASK_CTRANSLATE:
    _run_tasks({TASK_TYPE});
    _run_ctranslate();
    break;

  case TASK_BUILD_OBJECT:
    _run_tasks({TASK_CTRANSLATE}, true);
    _run_build_object();
    break;

  case TASK_BUILD_BINARY:
    _run_tasks({TASK_CTRANSLATE}, true);
    _run_build_binary();
    break;

  default:
    PANIC("cgen-cc: unknown task");
  };

  _tasks_done.insert(t);
}

void CGenCompiler::_run_parse() {

  if (_input_files.empty()) {
    PANIC("cgen-cc: no input file");
  }

  try {

    _parser = std::make_unique<cgen::Parser>();
    for (const auto &f : _input_files)
      _parser->parse_file(f);
    _ast = _parser->ast();

  } catch (obcl::LexerError &e) {
    compile_error(e);
  } catch (obcl::ParserError &e) {
    compile_error(e);
  }
}

void CGenCompiler::_run_type() {

  try {
    _type_ctx = std::make_unique<cgen::TypeContext>();
    _type_ctx->build(*_ast);
  } catch (cgen::TypeError &e) {
    compile_error(e);
  }
}

void CGenCompiler::_run_ctranslate() {
  std::ostream *os = nullptr;
  std::ofstream os_file;

  if (_output_c_file.empty()) {
    _output_c_file = _get_tmp_or_dft_path(_input_files.front(), ".c");
    os_file.open(_output_c_file);
    os = &os_file;
  } else if (_output_c_file == "-") {
    os = &std::cout;
  } else {
    os_file.open(_output_c_file);
    os = &os_file;
  }

  assert(os);
  _ctrans = std::make_unique<cgen::CTranslator>(*os);
  _ctrans->compile(*_ast);
}

void CGenCompiler::_run_build_object() {
  if (_output_object_file.empty())
    _output_object_file = _get_tmp_or_dft_path(_input_files.front(), ".o");

  obcl::bin::Compiler cc;
  if (_cc_debug)
    cc.set_debug(obcl::bin::Compiler::DebugMode::L3);
  cc.build_object(_output_c_file, _output_object_file);
}

void CGenCompiler::_run_build_binary() {
  if (_output_binary_file.empty())
    _output_binary_file = _get_tmp_or_dft_path(_input_files.front(), ".out");

  obcl::bin::Compiler cc;
  for (const auto &lib : _c_libs)
    cc.add_lib(lib);
  if (_cc_debug)
    cc.set_debug(obcl::bin::Compiler::DebugMode::L3);
  cc.build_bin({_output_c_file}, _output_binary_file);
}

std::string CGenCompiler::_get_tmp_or_dft_path(const std::string &input,
                                               const std::string &ext) {
  if (_build_tmp)
    return _get_tmp_path(ext);

  auto path = obcl::path::basename(input);
  return obcl::path::split_ext(path).first + ext;
}

std::string CGenCompiler::_get_tmp_path(const std::string &suffix) {
  static int id = 0;
  return "/tmp/cgen-cc_" + std::to_string(++id) + suffix;
}
