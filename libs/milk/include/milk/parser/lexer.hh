//===--parser/lexer.hh - Lexer utils ----------------------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains several informations to build a milk lexer
///
//===----------------------------------------------------------------------===//

#pragma once

#include "obcl/lexer/lexer.hh"

namespace milk {

static constexpr obcl::token_type_t TOK_KW_FN = 1301;
static constexpr obcl::token_type_t TOK_KW_TYPE = 1302;
static constexpr obcl::token_type_t TOK_KW_STRUCT = 1303;
static constexpr obcl::token_type_t TOK_KW_LET = 1304;
static constexpr obcl::token_type_t TOK_KW_CONST = 1305;
static constexpr obcl::token_type_t TOK_KW_ENUM = 1306;

static constexpr obcl::token_type_t TOK_SYM_LCBRAC = 1401;
static constexpr obcl::token_type_t TOK_SYM_RCBRAC = 1402;
static constexpr obcl::token_type_t TOK_SYM_LRBRAC = 1403;
static constexpr obcl::token_type_t TOK_SYM_RRBRAC = 1404;
static constexpr obcl::token_type_t TOK_SYM_LSBRAC = 1405;
static constexpr obcl::token_type_t TOK_SYM_RSBRAC = 1406;
static constexpr obcl::token_type_t TOK_SYM_COMA = 1407;
static constexpr obcl::token_type_t TOK_SYM_SEMI = 1408;
static constexpr obcl::token_type_t TOK_SYM_COLON = 1409;
static constexpr obcl::token_type_t TOK_SYM_DOT = 1410;

extern const obcl::Lexer::CustomTokenInfos token_infos_custom[];

} // namespace milk
