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

inline constexpr std::uint32_t ATTR_MREF = 1 << 24;  // 0 0 1
inline constexpr std::uint32_t ATTR_CREF = 2 << 24;  // 0 1 0
inline constexpr std::uint32_t ATTR_AMREF = 5 << 24; // 1 0 1
inline constexpr std::uint32_t ATTR_ACREF = 6 << 24; // 1 1 0

constexpr std::uint32_t build_code(std::uint32_t val, std::uint32_t attr) {
  return val | attr;
}

constexpr std::uint32_t get_val(std::uint32_t code) { return code & 0xFFFFFF; }

constexpr std::uint32_t get_attr(std::uint32_t code) {
  return code & 0xFF000000;
}

} // namespace typecode

} // namespace milk
