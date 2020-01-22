
set(AST_SRC
  ast/ast-visitor.cc
)

set(COMPILER_SRC
  compiler/compiler.cc
)

set(PARSER_SRC
  parser/lexer.cc
  parser/parser.cc
)

set(TYPE_SRC
  type/type-visitor.cc
)

set(SRC
  ${AST_SRC}
  ${COMPILER_SRC}
  ${PARSER_SRC}
  ${TYPE_SRC}
)

add_library(milk ${SRC})
target_link_libraries(milk obcl)
