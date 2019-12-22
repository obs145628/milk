#include "parser/lexer.hh"

//#define DEF_KW(X) {TOK_KW_ ## X, #X, "KW_" #X}

namespace milk {

const obcl::Lexer::CustomTokenInfos token_infos_custom[] = {

    {TOK_KW_FN, "fn", "KW_FN"},
    {TOK_KW_TYPE, "type", "KW_TYPE"},
    {TOK_KW_STRUCT, "struct", "KW_STRUCT"},
    {TOK_KW_LET, "let", "KW_LET"},
    {TOK_KW_CONST, "const", "KW_CONST"},
    {TOK_KW_ENUM, "enum", "KW_ENUM"},

    {0, "", ""}};

}

//#undef DEF_KW
