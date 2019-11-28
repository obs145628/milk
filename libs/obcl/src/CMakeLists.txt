
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
  utils/debug.cc
)

set(SRC
  ${LEXER_SRC}
  ${PARSER_SRC}
  ${UTILS_SRC}
)

add_library(obcl ${SRC})
