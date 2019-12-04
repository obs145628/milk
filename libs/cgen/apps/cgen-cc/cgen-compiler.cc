#include "cgen-compiler.hh"
#include "cgen/types/type-error.hh"
#include "obcl/lexer/lexer-error.hh"
#include "obcl/parser/parser-error.hh"
#include "obcl/utils/debug.hh"
#include <cstdlib>
#include <fstream>
#include <iostream>

CGenCompiler::CGenCompiler() : _ast(nullptr) {}

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

void CGenCompiler::_run_tasks(const std::vector<task_t> &tasks) {
  for (const auto &t : tasks)
    _run_task(t);
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

  std::cout << "Got " << _ast->defs().size() << " definitions." << std::endl;
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
    auto path = "t";
    os_file.open(path);
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
