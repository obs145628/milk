
set(PARSER_SRC
  parser/lexer.cc
)

set(SRC
  ${PARSER_SRC}
)

add_library(cgen ${SRC})
target_link_libraries(cgen obcl)
