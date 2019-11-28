//===--ast/all.hh - All AST classes -----------------------------*- C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file simply includes the header files for oll AST Node types
/// declaration
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-def-fun.hh"
#include "ast-def-struct.hh"
#include "ast-def-type.hh"
#include "ast-def-var.hh"
#include "ast-def.hh"
#include "ast-expr-bin-op.hh"
#include "ast-expr-call.hh"
#include "ast-expr-cast.hh"
#include "ast-expr-field.hh"
#include "ast-expr-float.hh"
#include "ast-expr-id.hh"
#include "ast-expr-int.hh"
#include "ast-expr-sizeof.hh"
#include "ast-expr-string.hh"
#include "ast-expr-un-op.hh"
#include "ast-expr.hh"
#include "ast-instr-block.hh"
#include "ast-instr-break.hh"
#include "ast-instr-continue.hh"
#include "ast-instr-expr.hh"
#include "ast-instr-if.hh"
#include "ast-instr-return.hh"
#include "ast-instr-var.hh"
#include "ast-instr-while.hh"
#include "ast-instr.hh"
#include "ast-program.hh"
#include "ast-type-id-name.hh"
#include "ast-type-id-pointer.hh"
#include "ast-type-id.hh"
#include "ast.hh"
