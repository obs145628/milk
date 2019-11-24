
set(LEXER_SRC
  lexer/lexer-error.cc
  lexer/location.cc
  lexer/position.cc
  lexer/token.cc
)

set(SRC
  ${LEXER_SRC}
)

add_library(obcl ${SRC})
