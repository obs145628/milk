#include "compiler/compiler.hh"
#include "ast/all.hh"
#include "parser/parser.hh"

#include "obcl/lexer/lexer-error.hh"
#include "obcl/parser/parser-error.hh"

#include <cstdlib>
#include <iostream>
#include <memory>

namespace milk {

namespace {

void compile_error(const std::exception &e) {
  std::cerr << "Compilation failed: " << std::endl << e.what();
  std::exit(1);
}

} // namespace

Compiler::Compiler() {}

void Compiler::parse_file(const std::string &path) {
  (void)path;
  (void)path;

  auto parser = std::make_unique<Parser>();

  try {

    parser->parse_file(path);
  } catch (obcl::LexerError &e) {
    compile_error(e);
  } catch (obcl::ParserError &e) {
    compile_error(e);
  }
}

} // namespace milk
