//===--type/type-codes.hh - TypeSimple code ---------------------*- C++ -*-===//
//
// milk compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contain constants and tools to handle codes for all TypeSimple
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cstdint>

namespace milk {

namespace typecode {

inline constexpr std::uint32_t CODE_VOID = 0;
inline constexpr std::uint32_t CODE_U8 = 11;
inline constexpr std::uint32_t CODE_U16 = 12;
inline constexpr std::uint32_t CODE_U32 = 13;
inline constexpr std::uint32_t CODE_U64 = 14;
inline constexpr std::uint32_t CODE_I8 = 15;
inline constexpr std::uint32_t CODE_I16 = 16;
inline constexpr std::uint32_t CODE_I32 = 17;
inline constexpr std::uint32_t CODE_I64 = 18;
inline constexpr std::uint32_t CODE_F32 = 19;
inline constexpr std::uint32_t CODE_F64 = 20;

inline constexpr std::uint32_t CODE_START_STRUCT = 100000;
inline constexpr std::uint32_t CODE_START_ENUM = 200000;

} // namespace typecode

} // namespace milk
