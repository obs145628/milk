set(BINCL_SRC
  bincl/compiler.cc
)

set(LEXER_SRC
  lexer/lexer.cc
  lexer/lexer-error.cc
  lexer/location.cc
  lexer/position.cc
  lexer/token.cc
  lexer/trie.cc
)

set(PARSER_SRC
  parser/parser.cc
  parser/parser-error.cc
)

set(UTILS_SRC
  utils/arguments.cc
  utils/debug.cc
  utils/io.cc
  utils/ipc.cc
  utils/path.cc
  utils/str.cc
)

set(SRC
  ${BINCL_SRC}
  ${LEXER_SRC}
  ${PARSER_SRC}
  ${UTILS_SRC}
)

add_library(obcl ${SRC})
