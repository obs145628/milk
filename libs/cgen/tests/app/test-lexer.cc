#include "obcl/lexer/lexer-error.hh"
#include "obcl/lexer/lexer.hh"
#include "parser/lexer.hh"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: ./cgen-test-lexer <sourcefile>" << std::endl;
    return 2;
  }

  std::ofstream os("out_tokens.txt");

  obcl::Lexer lex(cgen::token_infos_custom);
  lex.set_stream_file(argv[1]);

  try {

    while (lex.peek_token().type != obcl::TOK_EOF)
      os << lex.get_token() << std::endl;
  }

  catch (obcl::LexerError &err) {
    std::cerr << "Compilation error: " << std::endl << err.what() << std::endl;
    return 2;
  }

  return 0;
}
