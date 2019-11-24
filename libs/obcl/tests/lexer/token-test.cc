#include "lexer/stream.hh"
#include "lexer/token.hh"
#include <catch2/catch.hpp>
#include <memory>
#include <sstream>

TEST_CASE("Test ocbl::Token::type_str", "[obcl_token_type_str]") {

  obcl::Stream mock_is("mock", std::make_unique<std::istringstream>(""));
  obcl::Position mock_pos(0, 0, 0, &mock_is);
  obcl::Location mock_loc(mock_pos, mock_pos);

  obcl::Token t1(mock_loc, obcl::TOK_ID, "hello");
  REQUIRE(t1.type_str() == std::string("ID"));

  constexpr obcl::token_type_t KW_WHILE = 67;
  obcl::Token::add_type(KW_WHILE, "KW_WHILE");

  obcl::Token t2(mock_loc, KW_WHILE, "while");
  REQUIRE(t2.type_str() == std::string("KW_WHILE"));
}

TEST_CASE("Test ocbl::Token conversion to int, float, etc",
          "[obcl_token_conversionsr]") {

  obcl::Stream mock_is("mock", std::make_unique<std::istringstream>(""));
  obcl::Position mock_pos(0, 0, 0, &mock_is);
  obcl::Location mock_loc(mock_pos, mock_pos);

  obcl::Token t1(mock_loc, obcl::TOK_CONST_INT, "48");
  REQUIRE(t1.get_int() == 48);

  obcl::Token t2(mock_loc, obcl::TOK_CONST_FLOAT, "57.5");
  REQUIRE(t2.get_float() == 57.5);
}
