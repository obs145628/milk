//#define CATCH_CONFIG_MAIN
//#include <catch2/catch.hpp>
#include <iostream>

#include "lexer/stream.hh"

/*
int fact(int x) { return x <= 1 ? 1 : x * fact(x - 1); }

TEST_CASE(" Factorials are computed", "[factorial1]") {
  REQUIRE(fact(0) == 1);
  REQUIRE(fact(1) == 1);
  REQUIRE(fact(2) == 2);
  REQUIRE(fact(3) == 6);
  REQUIRE(fact(4) == 24);
  REQUIRE(fact(10) == 3628800);
}
*/

int main() {

  int z = 56;

#ifdef __GNUC__
  std::cout << "g++: " << __GNUC__ << "." << __GNUC_MINOR__ << std::endl;
#endif

#ifdef __clang__
  std::cout << "clang++ " << __clang_major__ << "." << __clang_minor__ << "."
            << __clang_patchlevel__ << std::endl;
#endif

  int *x = new int;
  *x = 4;
}
