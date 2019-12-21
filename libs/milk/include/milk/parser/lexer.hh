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

extern const obcl::Lexer::CustomTokenInfos token_infos_custom[];

} // namespace milk
