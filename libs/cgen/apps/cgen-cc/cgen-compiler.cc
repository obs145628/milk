#include "cgen-compiler.hh"
#include "obcl/lexer/lexer-error.hh"
#include "obcl/parser/parser-error.hh"
#include "obcl/utils/debug.hh"
#include <cstdlib>
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
  default:
    PANIC("cgen-cc: unknown task");
  };

  _tasks_done.insert(t);
}

void CGenCompiler::_run_parse() {

  if (_input_file.empty()) {
    PANIC("cgen-cc: no input file");
  }

  try {

    _parser = std::make_unique<cgen::Parser>();
    _parser->parse_file(_input_file);
    _ast = _parser->ast();

  } catch (obcl::LexerError &e) {
    compile_error(e);
  } catch (obcl::ParserError &e) {
    compile_error(e);
  }

  std::cout << "Got " << _ast->defs().size() << " definitions." << std::endl;
}
