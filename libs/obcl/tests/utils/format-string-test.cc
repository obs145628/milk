#include "utils/format-string.hh"
#include <catch2/catch.hpp>

TEST_CASE("Test ocbl::format-string simple", "[obcl_format_string_simple") {

  auto res = FORMAT_STRING("Hello, I " << 12 << " si \nfin.");
  REQUIRE(res == "Hello, I 12 si \nfin.");
}
