set(SRC
    type-builder.cc
    type-check.cc
    type-context.cc
    type-context-binop.cc
    type-context-unop.cc
    type-error.cc
    type-infos.cc
    type-visitor.cc
)
add_library(cgen_types ${SRC})
target_link_libraries(cgen_types cgen_ast strutils)
