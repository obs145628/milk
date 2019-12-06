set(SRC_BINCL
  bincl/compiler-test.cc
)

set(SRC_LEXER
  lexer/lexer-test.cc
  lexer/location-test.cc
  lexer/stream-test.cc
  lexer/token-test.cc
)

set(SRC_UTILS
  utils/arguments-test.cc
  utils/ipc-test.cc
  utils/format-string-test.cc
  utils/path-test.cc
  utils/str-test.cc
)


set(SRC
  ${SRC_BINCL}
  ${SRC_LEXER}
  ${SRC_UTILS}
  main.cc
)

add_executable(tmpbin_tests_obcl EXCLUDE_FROM_ALL ${SRC})
target_link_libraries(tmpbin_tests_obcl obcl)


add_custom_target(check-obcl
   COMMAND $<TARGET_FILE:tmpbin_tests_obcl>
   DEPENDS tmpbin_tests_obcl
)
