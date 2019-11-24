//===-- lexer/location.hh - Location struct definition ----------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the struct Location
///
//===----------------------------------------------------------------------===//

#pragma once

#include "position.hh"
#include <cassert>
#include <ostream>

namespace obcl {

/// Represent the position of a string in the source code
/// This is an interval between the posiiton of 2 characters
/// begin is first char
/// end is last char (not like an iterator)
struct Location {

  /// First char (included) in the interval
  Position begin;

  /// Last char (included) in the interval
  /// Not like iterators (end one past last)
  Position end;

  /// \p begin must be before \p end
  Location(const Position &begin, const Position &end)
      : begin(begin), end(end) {}

  /// create a new location that covers both locations
  /// \p begin must be before \p end
  Location(const Location &begin, const Location &end)
      : Location(begin.begin, end.end) {}

  /// Returns the first location of a sequence
  /// @param container - sequence of localized items
  /// Each item of the sequence must have a ->loc() method that returns a
  /// Location container can't be empty
  template <class T> static Location begin_of(const T &container) {
    assert(!container.empty());
    return container.front()->loc();
  }

  /// Returns the last location of a sequence
  /// @param container - sequence of localized items
  /// Each item of the sequence must have a ->loc() method that returns a
  /// Location container can't be empty
  template <class T> static Location end_of(const T &container) {
    assert(!container.empty());
    return container.back()->loc();
  }

  /// Display the corresponding code of the location
  /// Display the exact location, and part of the source code
  /// Used to report errors to the user
  void pretty_print_code(std::ostream &os) const;
};

/// Dump a Location. for debug purposes only
std::ostream &operator<<(std::ostream &os, const Location &loc);

} // namespace obcl
