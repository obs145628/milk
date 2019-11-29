set(SRC
  cgen-compiler.cc
  main.cc
)

add_executable(cgen-cc ${SRC})
target_link_libraries(cgen-cc obcl cgen)
