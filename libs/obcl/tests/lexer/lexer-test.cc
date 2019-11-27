#include "lexer/lexer.hh"
#include <catch2/catch.hpp>

namespace {

static constexpr obcl::token_type_t OP_INC = 101;
static constexpr obcl::token_type_t OP_DEC = 102;
static constexpr obcl::token_type_t OP_DOT = 103;
static constexpr obcl::token_type_t OP_ARROW = 104;
static constexpr obcl::token_type_t OP_ADD = 105;
static constexpr obcl::token_type_t OP_SUB = 106;
static constexpr obcl::token_type_t OP_MUL = 107;
static constexpr obcl::token_type_t OP_DIV = 108;
static constexpr obcl::token_type_t OP_MOD = 109;
static constexpr obcl::token_type_t OP_NOT = 110;
static constexpr obcl::token_type_t OP_BNOT = 111;
static constexpr obcl::token_type_t OP_BLS = 112;
static constexpr obcl::token_type_t OP_BRS = 113;
static constexpr obcl::token_type_t OP_LE = 114;
static constexpr obcl::token_type_t OP_LT = 115;
static constexpr obcl::token_type_t OP_GE = 116;
static constexpr obcl::token_type_t OP_GT = 117;
static constexpr obcl::token_type_t OP_EQ = 118;
static constexpr obcl::token_type_t OP_NE = 119;
static constexpr obcl::token_type_t OP_BAND = 120;
static constexpr obcl::token_type_t OP_BOR = 121;
static constexpr obcl::token_type_t OP_BXOR = 122;
static constexpr obcl::token_type_t OP_AND = 123;
static constexpr obcl::token_type_t OP_OR = 124;
static constexpr obcl::token_type_t SYM_LPAREN = 125;
static constexpr obcl::token_type_t SYM_RPAREN = 126;
static constexpr obcl::token_type_t SYM_LSBRACK = 127;
static constexpr obcl::token_type_t SYM_RSBRACK = 128;
static constexpr obcl::token_type_t SYM_LCBRACK = 129;
static constexpr obcl::token_type_t SYM_RCBRACK = 130;
static constexpr obcl::token_type_t SYM_COMMA = 131;
static constexpr obcl::token_type_t SYM_SEMI = 132;
static constexpr obcl::token_type_t KW_IF = 133;
static constexpr obcl::token_type_t KW_ELSE = 134;
static constexpr obcl::token_type_t KW_FOR = 135;
static constexpr obcl::token_type_t KW_WHILE = 136;
static constexpr obcl::token_type_t KW_BREAK = 137;
static constexpr obcl::token_type_t KW_CONTINUE = 138;
static constexpr obcl::token_type_t KW_CASE = 139;

const obcl::Lexer::CustomTokenInfos CUSTOM_C[] = {
    {OP_INC, "++", "OP_INC"},
    {OP_DEC, "--", "OP_DEC"},
    {OP_DOT, ".", "OP_DOT"},
    {OP_ARROW, "->", "OP_ARROW"},
    {OP_ADD, "+", "OP_ADD"},
    {OP_SUB, "-", "OP_SUB"},
    {OP_MUL, "*", "OP_MUL"},
    {OP_DIV, "/", "OP_DIV"},
    {OP_MOD, "%", "OP_MOD"},
    {OP_NOT, "!", "OP_NOT"},
    {OP_BNOT, "~", "OP_BNOT"},
    {OP_BLS, "<<", "OP_BLS"},
    {OP_BRS, ">>", "OP_BRS"},
    {OP_LE, "<=", "OP_LE"},
    {OP_LT, "<", "OP_LT"},
    {OP_GE, ">=", "OP_GE"},
    {OP_GT, ">", "OP_GT"},
    {OP_EQ, "==", "OP_EQ"},
    {OP_NE, "!=", "OP_NE"},
    {OP_BAND, "&", "OP_BAND"},
    {OP_BOR, "!", "OP_BOR"},
    {OP_BXOR, "^", "OP_BXOR"},
    {OP_AND, "&&", "OP_AND"},
    {OP_OR, "||", "OP_OR"},
    {SYM_LPAREN, "(", "SYM_LPAREN"},
    {SYM_RPAREN, ")", "SYM_RPAREN"},
    {SYM_LSBRACK, "[", "SYM_LSBRACK"},
    {SYM_RSBRACK, "]", "SYM_RSBRACK"},
    {SYM_LCBRACK, "{", "SYM_LCBRACK"},
    {SYM_RCBRACK, "}", "SYM_RCBRACK"},
    {SYM_COMMA, ",", "OP_COMA"},
    {SYM_SEMI, ";", "OP_SEMI"},
    {KW_IF, "if", "KW_IF"},
    {KW_ELSE, "else", "kW_ELSE"},
    {KW_FOR, "for", "KW_FOR"},
    {KW_WHILE, "while", "KW_WHILE"},
    {KW_BREAK, "break", "KW_BREAK"},
    {KW_CONTINUE, "continue", "kW_CONTINUE"},
    {KW_CASE, "case", "KW_CASE"},
    {0, "", ""},
};

obcl::Lexer &get_lexer() {
  static obcl::Lexer lex(CUSTOM_C);
  return lex;
}

} // namespace

TEST_CASE("Test obcl:::Lexer empty", "[obcl_lexer_empty") {
  const char *data = "";
  auto &lex = get_lexer();
  lex.set_stream_raw(data);
  REQUIRE(lex.peek_token().type == obcl::TOK_EOF);
  REQUIRE(lex.get_token().type == obcl::TOK_EOF);
}

TEST_CASE("Test obcl:::Lexer strings basic", "[obcl_lexer_strings_basic") {
  const char *data = "  \"abc\"   'tozy'\"1\" ''\"\"    ";
  auto &lex = get_lexer();
  lex.set_stream_raw(data);

  auto t1 = lex.get_token();
  REQUIRE(t1.type == obcl::TOK_CONST_DQ);
  REQUIRE(t1.val == "\"abc\"");
  REQUIRE(t1.loc.begin.row == 1);
  REQUIRE(t1.loc.begin.col == 3);
  REQUIRE(t1.loc.end.row == 1);
  REQUIRE(t1.loc.end.col == 7);

  auto t2 = lex.get_token();
  REQUIRE(t2.type == obcl::TOK_CONST_SQ);
  REQUIRE(t2.val == "'tozy'");
  REQUIRE(t2.loc.begin.row == 1);
  REQUIRE(t2.loc.begin.col == 11);
  REQUIRE(t2.loc.end.row == 1);
  REQUIRE(t2.loc.end.col == 16);

  auto t3 = lex.get_token();
  REQUIRE(t3.type == obcl::TOK_CONST_DQ);
  REQUIRE(t3.val == "\"1\"");
  REQUIRE(t3.loc.begin.row == 1);
  REQUIRE(t3.loc.begin.col == 17);
  REQUIRE(t3.loc.end.row == 1);
  REQUIRE(t3.loc.end.col == 19);

  auto t4 = lex.get_token();
  REQUIRE(t4.type == obcl::TOK_CONST_SQ);
  REQUIRE(t4.val == "''");
  REQUIRE(t4.loc.begin.row == 1);
  REQUIRE(t4.loc.begin.col == 21);
  REQUIRE(t4.loc.end.row == 1);
  REQUIRE(t4.loc.end.col == 22);

  auto t5 = lex.get_token();
  REQUIRE(t5.type == obcl::TOK_CONST_DQ);
  REQUIRE(t5.val == "\"\"");
  REQUIRE(t5.loc.begin.row == 1);
  REQUIRE(t5.loc.begin.col == 23);
  REQUIRE(t5.loc.end.row == 1);
  REQUIRE(t5.loc.end.col == 24);

  REQUIRE(lex.get_token().type == obcl::TOK_EOF);
}

TEST_CASE("Test obcl:::Lexer number basic", "[obcl_lexer_number_basic") {
  const char *data = "  124  5 0 0.12     1874.923   ";
  auto &lex = get_lexer();
  lex.set_stream_raw(data);

  auto t1 = lex.get_token();
  REQUIRE(t1.type == obcl::TOK_CONST_INT);
  REQUIRE(t1.val == "124");
  REQUIRE(t1.loc.begin.row == 1);
  REQUIRE(t1.loc.begin.col == 3);
  REQUIRE(t1.loc.end.row == 1);
  REQUIRE(t1.loc.end.col == 5);

  auto t2 = lex.get_token();
  REQUIRE(t2.type == obcl::TOK_CONST_INT);
  REQUIRE(t2.val == "5");
  REQUIRE(t2.loc.begin.row == 1);
  REQUIRE(t2.loc.begin.col == 8);
  REQUIRE(t2.loc.end.row == 1);
  REQUIRE(t2.loc.end.col == 8);

  auto t3 = lex.get_token();
  REQUIRE(t3.type == obcl::TOK_CONST_INT);
  REQUIRE(t3.val == "0");
  REQUIRE(t3.loc.begin.row == 1);
  REQUIRE(t3.loc.begin.col == 10);
  REQUIRE(t3.loc.end.row == 1);
  REQUIRE(t3.loc.end.col == 10);

  auto t4 = lex.get_token();
  REQUIRE(t4.type == obcl::TOK_CONST_FLOAT);
  REQUIRE(t4.val == "0.12");
  REQUIRE(t4.loc.begin.row == 1);
  REQUIRE(t4.loc.begin.col == 12);
  REQUIRE(t4.loc.end.row == 1);
  REQUIRE(t4.loc.end.col == 15);

  auto t5 = lex.get_token();
  REQUIRE(t5.type == obcl::TOK_CONST_FLOAT);
  REQUIRE(t5.val == "1874.923");
  REQUIRE(t5.loc.begin.row == 1);
  REQUIRE(t5.loc.begin.col == 21);
  REQUIRE(t5.loc.end.row == 1);
  REQUIRE(t5.loc.end.col == 28);

  REQUIRE(lex.get_token().type == obcl::TOK_EOF);
}

TEST_CASE("Test obcl:::Lexer id basic", "[obcl_lexer_id_basic") {
  const char *data = "  foo  x salamandre  ";
  auto &lex = get_lexer();
  lex.set_stream_raw(data);

  auto t1 = lex.get_token();
  REQUIRE(t1.type == obcl::TOK_ID);
  REQUIRE(t1.val == "foo");
  REQUIRE(t1.loc.begin.row == 1);
  REQUIRE(t1.loc.begin.col == 3);
  REQUIRE(t1.loc.end.row == 1);
  REQUIRE(t1.loc.end.col == 5);

  auto t2 = lex.get_token();
  REQUIRE(t2.type == obcl::TOK_ID);
  REQUIRE(t2.val == "x");
  REQUIRE(t2.loc.begin.row == 1);
  REQUIRE(t2.loc.begin.col == 8);
  REQUIRE(t2.loc.end.row == 1);
  REQUIRE(t2.loc.end.col == 8);

  auto t3 = lex.get_token();
  REQUIRE(t3.type == obcl::TOK_ID);
  REQUIRE(t3.val == "salamandre");
  REQUIRE(t3.loc.begin.row == 1);
  REQUIRE(t3.loc.begin.col == 10);
  REQUIRE(t3.loc.end.row == 1);
  REQUIRE(t3.loc.end.col == 19);

  REQUIRE(lex.get_token().type == obcl::TOK_EOF);
}

TEST_CASE("Test obcl:::Lexer customnonid basic",
          "[obcl_lexer_customnonid_basic") {
  const char *data = "  ; {} +-++";
  auto &lex = get_lexer();
  lex.set_stream_raw(data);

  auto t1 = lex.get_token();
  REQUIRE(t1.type == SYM_SEMI);
  REQUIRE(t1.val == ";");
  REQUIRE(t1.loc.begin.row == 1);
  REQUIRE(t1.loc.begin.col == 3);
  REQUIRE(t1.loc.end.row == 1);
  REQUIRE(t1.loc.end.col == 3);

  auto t2 = lex.get_token();
  REQUIRE(t2.type == SYM_LCBRACK);
  REQUIRE(t2.val == "{");
  REQUIRE(t2.loc.begin.row == 1);
  REQUIRE(t2.loc.begin.col == 5);
  REQUIRE(t2.loc.end.row == 1);
  REQUIRE(t2.loc.end.col == 5);

  auto t3 = lex.get_token();
  REQUIRE(t3.type == SYM_RCBRACK);
  REQUIRE(t3.val == "}");
  REQUIRE(t3.loc.begin.row == 1);
  REQUIRE(t3.loc.begin.col == 6);
  REQUIRE(t3.loc.end.row == 1);
  REQUIRE(t3.loc.end.col == 6);

  auto t4 = lex.get_token();
  REQUIRE(t4.type == OP_ADD);
  REQUIRE(t4.val == "+");
  REQUIRE(t4.loc.begin.row == 1);
  REQUIRE(t4.loc.begin.col == 8);
  REQUIRE(t4.loc.end.row == 1);
  REQUIRE(t4.loc.end.col == 8);

  auto t5 = lex.get_token();
  REQUIRE(t5.type == OP_SUB);
  REQUIRE(t5.val == "-");
  REQUIRE(t5.loc.begin.row == 1);
  REQUIRE(t5.loc.begin.col == 9);
  REQUIRE(t5.loc.end.row == 1);
  REQUIRE(t5.loc.end.col == 9);

  auto t6 = lex.get_token();
  REQUIRE(t6.type == OP_INC);
  REQUIRE(t6.val == "++");
  REQUIRE(t6.loc.begin.row == 1);
  REQUIRE(t6.loc.begin.col == 10);
  REQUIRE(t6.loc.end.row == 1);
  REQUIRE(t6.loc.end.col == 11);

  REQUIRE(lex.get_token().type == obcl::TOK_EOF);
}

TEST_CASE("Test obcl:::Lexer id custom", "[obcl_lexer_id_custom") {
  const char *data = "  for foo while";
  auto &lex = get_lexer();
  lex.set_stream_raw(data);

  auto t1 = lex.get_token();
  REQUIRE(t1.type == KW_FOR);
  REQUIRE(t1.val == "for");
  REQUIRE(t1.loc.begin.row == 1);
  REQUIRE(t1.loc.begin.col == 3);
  REQUIRE(t1.loc.end.row == 1);
  REQUIRE(t1.loc.end.col == 5);

  auto t2 = lex.get_token();
  REQUIRE(t2.type == obcl::TOK_ID);
  REQUIRE(t2.val == "foo");
  REQUIRE(t2.loc.begin.row == 1);
  REQUIRE(t2.loc.begin.col == 7);
  REQUIRE(t2.loc.end.row == 1);
  REQUIRE(t2.loc.end.col == 9);

  auto t3 = lex.get_token();
  REQUIRE(t3.type == KW_WHILE);
  REQUIRE(t3.val == "while");
  REQUIRE(t3.loc.begin.row == 1);
  REQUIRE(t3.loc.begin.col == 11);
  REQUIRE(t3.loc.end.row == 1);
  REQUIRE(t3.loc.end.col == 15);

  REQUIRE(lex.get_token().type == obcl::TOK_EOF);
}
