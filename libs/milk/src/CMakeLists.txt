
set(AST_SRC
  ast/ast-visitor.cc
)

set(PARSER_SRC
  parser/lexer.cc
  parser/parser.cc
)

set(SRC
  ${AST_SRC}
  ${PARSER_SRC}
)

add_library(milk ${SRC})
target_link_libraries(milk obcl)
