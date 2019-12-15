
set(AST_SRC
  ast/ast-visitor.cc
)

set(SRC
  ${AST_SRC}
)

add_library(milk ${SRC})
target_link_libraries(milk obcl)
