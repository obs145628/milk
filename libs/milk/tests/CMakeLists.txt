

add_custom_target(check-milk-parser
  COMMAND  MILK_CL_TEST=parse python3 ${CMAKE_CURRENT_SOURCE_DIR}/apps/test-compiler.py
  ${PROJECT_BINARY_DIR}
  DEPENDS mkcl
)

add_custom_target(check-milk
  DEPENDS check-milk-parser
)
