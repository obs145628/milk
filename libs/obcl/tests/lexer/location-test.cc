#include "lexer/location.hh"
#include "lexer/stream.hh"
#include <catch2/catch.hpp>
#include <memory>
#include <sstream>
#include <vector>

class MyLoc {
public:
  MyLoc(const obcl::Location &loc) : _loc(loc) {}

  const obcl::Location &loc() const { return _loc; }

private:
  obcl::Location _loc;
};

TEST_CASE("Test ocbl::location::begin_end_of", "[obcl_location_begin_end_of]") {

  obcl::Stream st("mock", std::make_unique<std::istringstream>(""));

  obcl::Location l1(obcl::Position(1, 1, 0, &st),
                    obcl::Position(1, 15, 0, &st));
  obcl::Location l2(obcl::Position(2, 1, 0, &st),
                    obcl::Position(2, 18, 0, &st));
  obcl::Location l3(obcl::Position(3, 1, 0, &st),
                    obcl::Position(3, 12, 0, &st));
  obcl::Location l4(obcl::Position(4, 1, 0, &st),
                    obcl::Position(4, 26, 0, &st));

  std::vector<std::unique_ptr<MyLoc>> v;
  v.push_back(std::make_unique<MyLoc>(l1));
  v.push_back(std::make_unique<MyLoc>(l2));
  v.push_back(std::make_unique<MyLoc>(l3));
  v.push_back(std::make_unique<MyLoc>(l4));

  auto beg = obcl::Location::begin_of(v);
  REQUIRE(beg.begin.row == l1.begin.row);
  REQUIRE(beg.begin.col == l1.begin.col);
  REQUIRE(beg.end.row == l1.end.row);
  REQUIRE(beg.end.col == l1.end.col);

  auto end = obcl::Location::end_of(v);
  REQUIRE(end.begin.row == l4.begin.row);
  REQUIRE(end.begin.col == l4.begin.col);
  REQUIRE(end.end.row == l4.end.row);
  REQUIRE(end.end.col == l4.end.col);
}
