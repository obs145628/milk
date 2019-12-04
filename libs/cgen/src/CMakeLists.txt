
set(AST_SRC
  ast/ast-visitor.cc
)

set(CTRANSLATOR_SRC
  ctranslator/ctranslator.cc
)
  
set(PARSER_SRC
  parser/lexer.cc
  parser/parser.cc
)

set(TYPES_SRC
  types/type-builder.cc
  types/type-check.cc
  types/type-context-binop.cc
  types/type-context-unop.cc
  types/type-context.cc
  types/type-error.cc
  types/type-infos.cc
  types/type-visitor.cc
)


set(SRC
  ${AST_SRC}
  ${CTRANSLATOR_SRC}
  ${PARSER_SRC}
  ${TYPES_SRC}
)

add_library(cgen ${SRC})
target_link_libraries(cgen obcl)
