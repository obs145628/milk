#include "utils/arguments.hh"
#include <catch2/catch.hpp>

TEST_CASE("Test ocbl::Arguments flags", "[obcl_arguments_flags") {
  const char *data[] = {"./app", "todo",  "--foo", "no",
                        "--bar", "--tut", "x",     "y"};

  obcl::Arguments args;
  args.add_flag("foo", "");
  args.add_flag("bar", "");
  args.add_flag("tu", "");
  args.add_flag("ut", "");
  args.add_flag("tut", "");
  args.run(8, data);
  REQUIRE(args.all().size() == 8);

  auto other = args.other();
  REQUIRE(other.size() == 4);
  REQUIRE(other[0] == "todo");
  REQUIRE(other[1] == "no");
  REQUIRE(other[2] == "x");
  REQUIRE(other[3] == "y");

  REQUIRE(args.has_flag("foo"));
  REQUIRE(args.has_flag("bar"));
  REQUIRE(!args.has_flag("tu"));
  REQUIRE(!args.has_flag("ut"));
  REQUIRE(args.has_flag("tut"));
}

TEST_CASE("Test ocbl::Arguments options", "[obcl_arguments_options") {
  const char *data[] = {"./app", "todo", "--foo", "no", "--bar", "x", "y"};

  obcl::Arguments args;
  args.add_option("foo", "");
  args.add_option("bar", "", "up");
  args.add_option("tu", "", "ppp");
  args.add_option("ut", "");
  args.run(7, data);
  REQUIRE(args.all().size() == 7);

  auto other = args.other();
  REQUIRE(other.size() == 2);
  REQUIRE(other[0] == "todo");
  REQUIRE(other[1] == "y");

  REQUIRE(args.has_option("foo"));
  REQUIRE(args.has_option("bar"));
  REQUIRE(args.has_option("tu"));
  REQUIRE(!args.has_option("ut"));

  REQUIRE(args.get_option("foo") == "no");
  REQUIRE(args.get_option("bar") == "x");
  REQUIRE(args.get_option("tu") == "ppp");
}
