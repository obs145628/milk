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
static constexpr int ERR_LEX = 2;
static constexpr int ERR_PARSE = 3;
} // namespace

Compiler::Compiler() : _custom_ret_code(false) {}

void Compiler::parse_file(const std::string &path) {
  auto parser = std::make_unique<Parser>();

  try {
    parser->parse_file(path);
  } catch (obcl::LexerError &e) {
    _compile_error(e, ERR_LEX);
  } catch (obcl::ParserError &e) {
    _compile_error(e, ERR_PARSE);
  }
}

void Compiler::_compile_error(const std::exception &e, int code) {
  std::cerr << "Compilation failed: " << std::endl << e.what();
  std::exit(_custom_ret_code ? code : 1);
}

} // namespace milk
