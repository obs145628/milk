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

extern const obcl::Lexer::CustomTokenInfos token_infos_custom[];

} // namespace milk
