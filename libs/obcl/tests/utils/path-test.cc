#include "utils/path.hh"
#include <catch2/catch.hpp>

TEST_CASE("Test ocbl::path::basename_dirname simple",
          "[obcl_path_basename_dirname_simple") {

  std::string p1 = "abc/def/gh.txt";
  REQUIRE(obcl::path::basename(p1) == "gh.txt");
  REQUIRE(obcl::path::dirname(p1) == "abc/def");

  std::string p2 = "lolipop";
  REQUIRE(obcl::path::basename(p2) == "lolipop");
  REQUIRE(obcl::path::dirname(p2) == ".");
}

TEST_CASE("Test ocbl::path::split_ext", "[obcl_path_split_ext_simple") {

  auto r1 = obcl::path::split_ext("abc/def/gh.txt");
  REQUIRE(r1.first == "abc/def/gh");
  REQUIRE(r1.second == ".txt");

  auto r2 = obcl::path::split_ext("abc/def/gh");
  REQUIRE(r2.first == "abc/def/gh");
  REQUIRE(r2.second == "");

  auto r3 = obcl::path::split_ext("abc/def/gh.txt.gg");
  REQUIRE(r3.first == "abc/def/gh.txt");
  REQUIRE(r3.second == ".gg");
}
