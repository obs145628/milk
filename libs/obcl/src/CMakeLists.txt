
set(LEXER_SRC
  lexer/lexer.cc
  lexer/lexer-error.cc
  lexer/location.cc
  lexer/position.cc
  lexer/token.cc
  lexer/trie.cc
  )

set(UTILS_SRC
  utils/debug.cc
)

set(SRC
  ${LEXER_SRC}
  ${UTILS_SRC}
)

add_library(obcl ${SRC})
