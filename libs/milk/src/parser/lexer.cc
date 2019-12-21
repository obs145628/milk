#include "parser/lexer.hh"

namespace milk {

const obcl::Lexer::CustomTokenInfos token_infos_custom[] = {

    {TOK_KW_FN, "fn", "KW_FN"},

    {0, "", ""}};

}
