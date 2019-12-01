#include "utils/str.hh"
#include <catch2/catch.hpp>

TEST_CASE("Test ocbl::str::split simple", "[obcl_str_split_simple") {

  auto r1 = obcl::str::split("abcdef,tkt,u");
  REQUIRE(r1.size() == 3);
  REQUIRE(r1[0] == "abcdef");
  REQUIRE(r1[1] == "tkt");
  REQUIRE(r1[2] == "u");

  auto r2 = obcl::str::split("viva la vida");
  REQUIRE(r2.size() == 1);
  REQUIRE(r2[0] == "viva la vida");

  auto r3 = obcl::str::split(",ab,,,cd");
  REQUIRE(r3.size() == 5);
  REQUIRE(r3[0] == "");
  REQUIRE(r3[1] == "ab");
  REQUIRE(r3[2] == "");
  REQUIRE(r3[3] == "");
  REQUIRE(r3[4] == "cd");
}
