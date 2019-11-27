cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER /home/obs/local/llvm10/bin/clang CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /home/obs/local/llvm10/bin/clang++ CACHE PATH "" FORCE)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Werror -pedantic \
  -Wglobal-constructors"
)
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(SYSTEM "extern/Catch2/single_include")

project(mlk)

include_directories("libs/obcl/include/")
include_directories("libs/cgen/include/")

add_subdirectory(apps)
add_subdirectory(libs)
add_subdirectory(tests)
