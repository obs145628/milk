#include "lexer/stream.hh"
#include "lexer/token.hh"
#include <catch2/catch.hpp>
#include <memory>
#include <sstream>

namespace {
const char *DATA = "Hello, here is\n"
                   "a little test for\n"
                   "stream class\n";
}

TEST_CASE("Test ocbl::Stream empty", "[obcl_stream_empty") {
  obcl::Stream is("stream", std::make_unique<std::istringstream>(""));
  REQUIRE(is.get_char() == EOF);
  is.next();
  REQUIRE(is.get_char() == EOF);
}

TEST_CASE("Test ocbl::Stream read whole", "[obcl_stream_get_all]") {

  obcl::Stream is("stream", std::make_unique<std::istringstream>(DATA));
  std::string str;
  int c;
  while ((c = is.get_char()) != EOF) {
    str.push_back(c);
    is.next();
  }

  REQUIRE(str == DATA);

  is.next();
  REQUIRE(is.get_char() == EOF);
}

TEST_CASE("Test ocbl::Stream next/prev", "[obcl_stream_next_prev") {

  obcl::Stream is("stream", std::make_unique<std::istringstream>(DATA));

  REQUIRE(is.get_char() == 'H');
  REQUIRE(is.get_row() == 1);
  REQUIRE(is.get_col() == 1);
  REQUIRE(is.get_pos() == 0);

  is.next();
  REQUIRE(is.get_char() == 'e');
  REQUIRE(is.get_row() == 1);
  REQUIRE(is.get_col() == 2);
  REQUIRE(is.get_pos() == 1);

  is.prev();
  REQUIRE(is.get_row() == 1);
  REQUIRE(is.get_col() == 1);
  REQUIRE(is.get_pos() == 0);

  is.next();
  REQUIRE(is.get_char() == 'e');
  REQUIRE(is.get_row() == 1);
  REQUIRE(is.get_col() == 2);
  REQUIRE(is.get_pos() == 1);

  is.next();
  REQUIRE(is.get_char() == 'l');
  REQUIRE(is.get_row() == 1);
  REQUIRE(is.get_col() == 3);
  REQUIRE(is.get_pos() == 2);
}

TEST_CASE("Test ocbl::Stream next/prev at newline",
          "[obcl_stream_next_prev_newline") {

  obcl::Stream is("stream", std::make_unique<std::istringstream>(DATA));

  while (is.get_char() != '\n')
    is.next();
  auto last_col = is.get_col();
  auto last_pos = is.get_pos();
  REQUIRE(is.get_row() == 1);

  is.next();
  REQUIRE(is.get_char() == 'a');
  REQUIRE(is.get_row() == 2);
  REQUIRE(is.get_col() == 1);
  REQUIRE(is.get_pos() == last_pos + 1);

  is.prev();
  REQUIRE(is.get_char() == '\n');
  REQUIRE(is.get_row() == 1);
  REQUIRE(is.get_col() == last_col);
  REQUIRE(is.get_pos() == last_pos);

  is.next();
  REQUIRE(is.get_char() == 'a');
  REQUIRE(is.get_row() == 2);
  REQUIRE(is.get_col() == 1);
  REQUIRE(is.get_pos() == last_pos + 1);

  is.next();
  REQUIRE(is.get_char() == ' ');
  REQUIRE(is.get_row() == 2);
  REQUIRE(is.get_col() == 2);
  REQUIRE(is.get_pos() == last_pos + 2);
}
