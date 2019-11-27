#include "obcl/lexer/lexer.hh"
#include "parser/lexer.hh"
#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: ./cgen-test-lexer <sourcefile>" << std::endl;
    return 1;
  }

  std::ofstream os("out_tokens.txt");

  obcl::Lexer lex(cgen::token_infos_custom);
  lex.set_stream_file(argv[1]);
  while (lex.peek_token().type != obcl::TOK_EOF)
    os << lex.get_token() << std::endl;

  return 0;
}
