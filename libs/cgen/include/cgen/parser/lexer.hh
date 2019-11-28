//===--parser/lexer.hh - Lexer utils ----------------------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains several informations to build a cgen lexer
///
//===----------------------------------------------------------------------===//

#pragma once

#include "obcl/lexer/lexer.hh"

namespace cgen {

static constexpr obcl::token_type_t TOK_OP_ADD = 3101;
static constexpr obcl::token_type_t TOK_OP_SUB = 3102;
static constexpr obcl::token_type_t TOK_OP_MUL = 3103;
static constexpr obcl::token_type_t TOK_OP_DIV = 3104;
static constexpr obcl::token_type_t TOK_OP_MOD = 3105;
static constexpr obcl::token_type_t TOK_OP_NOT = 3106;
static constexpr obcl::token_type_t TOK_OP_BNOT = 3107;
static constexpr obcl::token_type_t TOK_OP_BLS = 3108;
static constexpr obcl::token_type_t TOK_OP_BRS = 3109;
static constexpr obcl::token_type_t TOK_OP_LE = 3110;
static constexpr obcl::token_type_t TOK_OP_LT = 3111;
static constexpr obcl::token_type_t TOK_OP_GE = 3112;
static constexpr obcl::token_type_t TOK_OP_GT = 3113;
static constexpr obcl::token_type_t TOK_OP_EQ = 3114;
static constexpr obcl::token_type_t TOK_OP_NE = 3115;
static constexpr obcl::token_type_t TOK_OP_BAND = 3116;
static constexpr obcl::token_type_t TOK_OP_BOR = 3117;
static constexpr obcl::token_type_t TOK_OP_BXOR = 3118;
static constexpr obcl::token_type_t TOK_OP_AND = 3119;
static constexpr obcl::token_type_t TOK_OP_OR = 3120;

static constexpr obcl::token_type_t TOK_SYM_LPAREN = 3201;
static constexpr obcl::token_type_t TOK_SYM_RPAREN = 3202;
static constexpr obcl::token_type_t TOK_SYM_LCBRACK = 3203;
static constexpr obcl::token_type_t TOK_SYM_RCBRACK = 3204;
static constexpr obcl::token_type_t TOK_SYM_COMMA = 3205;
static constexpr obcl::token_type_t TOK_SYM_SEMI = 3206;
static constexpr obcl::token_type_t TOK_SYM_COLON = 3207;
static constexpr obcl::token_type_t TOK_SYM_DOT = 3208;
static constexpr obcl::token_type_t TOK_SYM_EQ = 3209;

static constexpr obcl::token_type_t TOK_KW_FN = 3301;
static constexpr obcl::token_type_t TOK_KW_STRUCT = 3302;
static constexpr obcl::token_type_t TOK_KW_TYPE = 3303;
static constexpr obcl::token_type_t TOK_KW_VAR = 3304;
static constexpr obcl::token_type_t TOK_KW_IF = 3305;
static constexpr obcl::token_type_t TOK_KW_ELSE = 3306;
static constexpr obcl::token_type_t TOK_KW_WHILE = 3307;
static constexpr obcl::token_type_t TOK_KW_BREAK = 3308;
static constexpr obcl::token_type_t TOK_KW_CONTINUE = 3309;
static constexpr obcl::token_type_t TOK_KW_RETURN = 3310;
static constexpr obcl::token_type_t TOK_KW_SIZEOF = 3311;
static constexpr obcl::token_type_t TOK_KW_STATIC_CAST = 3312;
static constexpr obcl::token_type_t TOK_KW_PTR_CAST = 3313;
static constexpr obcl::token_type_t TOK_KW_REINTERPRET_CAST = 3314;

extern const obcl::Lexer::CustomTokenInfos token_infos_custom[];

} // namespace cgen
