
set(SRC_LEXER
  lexer/lexer-test.cc
  lexer/location-test.cc
  lexer/stream-test.cc
  lexer/token-test.cc
)

set(SRC
  ${SRC_LEXER}
  main.cc
)

set(SRC_TEST_LEXER
  app/test-lexer.cc
)

add_executable(cgen-test-lexer EXCLUDE_FROM_ALL ${SRC_TEST_LEXER})
target_link_libraries(cgen-test-lexer obcl cgen)

#add_executable(tmpbin_tests_obcl EXCLUDE_FROM_ALL ${SRC})
#target_link_libraries(tmpbin_tests_obcl obcl)


add_custom_target(check-cgen-lexer
  COMMAND  CGEN_CC_TEST=lex python3 ${CMAKE_CURRENT_SOURCE_DIR}/app/test-compiler.py
  ${PROJECT_BINARY_DIR}
  DEPENDS cgen-test-lexer
)

add_custom_target(check-cgen-parser
  COMMAND  CGEN_CC_TEST=parse python3 ${CMAKE_CURRENT_SOURCE_DIR}/app/test-compiler.py
  ${PROJECT_BINARY_DIR}
  DEPENDS cgen-cc cgen-test-lexer
)

add_custom_target(check-cgen-type
  COMMAND  CGEN_CC_TEST=type python3 ${CMAKE_CURRENT_SOURCE_DIR}/app/test-compiler.py
  ${PROJECT_BINARY_DIR}
  DEPENDS cgen-cc cgen-test-lexer
)

add_custom_target(check-cgen-compile
  COMMAND  CGEN_CC_TEST=compile python3 ${CMAKE_CURRENT_SOURCE_DIR}/app/test-compiler.py
  ${PROJECT_BINARY_DIR}
  DEPENDS cgen-cc cgen-test-lexer
)

add_custom_target(check-cgen-run
  COMMAND  CGEN_CC_TEST=run python3 ${CMAKE_CURRENT_SOURCE_DIR}/app/test-compiler.py
  ${PROJECT_BINARY_DIR}
  DEPENDS cgen-cc cgen-test-lexer
)

add_custom_target(check-cgen
  DEPENDS check-cgen-run
)
