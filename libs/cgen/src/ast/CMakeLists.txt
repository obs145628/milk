set(SRC
   ast-visitor
)
add_library(cgen_ast ${SRC})
target_link_libraries(cgen_ast lexy)
