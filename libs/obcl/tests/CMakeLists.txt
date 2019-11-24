
set(SRC_LEXER
  lexer/location-test.cc
  lexer/stream-test.cc
  lexer/token-test.cc
)

set(SRC
  ${SRC_LEXER}
  main.cc
)

add_executable(tmpbin_tests_obcl EXCLUDE_FROM_ALL ${SRC})
target_link_libraries(tmpbin_tests_obcl obcl)


add_custom_target(check-obcl
   COMMAND $<TARGET_FILE:tmpbin_tests_obcl>
   DEPENDS tmpbin_tests_obcl
)
