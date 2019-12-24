#include "parser/lexer.hh"

//#define DEF_KW(X) {TOK_KW_ ## X, #X, "KW_" #X}

#define DEF_SYM(NAME, REPR)                                                    \
  { TOK_SYM_##NAME, REPR, "KW_" #NAME }

namespace milk {

const obcl::Lexer::CustomTokenInfos token_infos_custom[] = {

    {TOK_KW_FN, "fn", "KW_FN"},
    {TOK_KW_TYPE, "type", "KW_TYPE"},
    {TOK_KW_STRUCT, "struct", "KW_STRUCT"},
    {TOK_KW_LET, "let", "KW_LET"},
    {TOK_KW_CONST, "const", "KW_CONST"},
    {TOK_KW_ENUM, "enum", "KW_ENUM"},

    DEF_SYM(LCBRAC, "{"),
    DEF_SYM(RRBRAC, "}"),
    DEF_SYM(LRBRAC, "("),
    DEF_SYM(RRBRAC, ")"),
    DEF_SYM(LSBRAC, "["),
    DEF_SYM(RSBRAC, "]"),
    DEF_SYM(COMA, ","),
    DEF_SYM(SEMI, ";"),
    DEF_SYM(COLON, ":"),
    DEF_SYM(DOT, "."),
    DEF_SYM(EQ, "="),

    {0, "", ""}};

}

//#undef DEF_KW
#undef DEF_SYM
