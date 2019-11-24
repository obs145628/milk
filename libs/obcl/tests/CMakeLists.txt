
set(SRC_LEXER
  lexer/location-test.cc
)

set(SRC
  ${SRC_LEXER}
)

#add_library(tests_obcl ${SRC})

add_executable(tmpbin_tests_obcl EXCLUDE_FROM_ALL ${SRC} main.cc)
#target_link_libraries(tmpbin_tests_obcl obcl)
#target_link_libraries(tmpbin_tests_obcl tests_obcl)


add_custom_target(check-obcl
   COMMAND $<TARGET_FILE:tmpbin_tests_obcl>
   DEPENDS tmpbin_tests_obcl
)
