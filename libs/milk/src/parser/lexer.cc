#include "parser/lexer.hh"

//#define DEF_KW(X) {TOK_KW_ ## X, #X, "KW_" #X}

#define DEF_KW(NAME, REPR)                                                     \
  { TOK_KW_##NAME, REPR, "KW_" #NAME }

#define DEF_SYM(NAME, REPR)                                                    \
  { TOK_SYM_##NAME, REPR, "KW_" #NAME }

namespace milk {

const obcl::Lexer::CustomTokenInfos token_infos_custom[] = {

    DEF_KW(FN, "fn"),
    DEF_KW(TYPE, "type"),
    DEF_KW(STRUCT, "struct"),
    DEF_KW(LET, "let"),
    DEF_KW(CONST, "const"),
    DEF_KW(ENUM, "enum"),
    DEF_KW(IF, "if"),
    DEF_KW(ELSE, "else"),
    DEF_KW(WHILE, "while"),
    DEF_KW(BREAK, "break"),
    DEF_KW(CONTINUE, "continue"),
    DEF_KW(RETURN, "return"),

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
    DEF_SYM(AND, "&"),
    DEF_SYM(CREF, "&const"),
    DEF_SYM(MAREF, "&[]"),
    DEF_SYM(CAREF, "&[]const"),
    DEF_SYM(ADD_EQ, "+="),
    DEF_SYM(SUB_EQ, "-="),
    DEF_SYM(MUL_EQ, "*="),
    DEF_SYM(DIV_EQ, "/="),
    DEF_SYM(MOD_EQ, "%="),
    DEF_SYM(QUESTION, "?"),

    {0, "", ""}};

}

#undef DEF_KW
#undef DEF_SYM
