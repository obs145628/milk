set(SRC
  main.cc
)

add_executable(mkcl ${SRC})
target_link_libraries(mkcl obcl cgen milk)
