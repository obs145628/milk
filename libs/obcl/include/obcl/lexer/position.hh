//===-- lexer/position.hh - Position struct definition ----------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the struct Position
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include <ostream>

namespace obcl {

/// The position is a lightweight struct
/// It represents the position of a characher in the source code
struct Position {

  /// line number (start at 1)
  std::size_t row;

  /// column number (start at 1)
  std::size_t col;

  /// ftell (or string index) exact position
  std::size_t pos;

  /// the source code unit
  Stream *stream;

  Position(std::size_t row, std::size_t col, std::size_t pos, Stream *stream)
      : row(row), col(col), pos(pos), stream(stream) {}
};

/// Dump a Position. for debug purposes only
std::ostream &operator<<(std::ostream &os, const Position &pos);

} // namespace obcl
