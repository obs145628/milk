//===-- utils/format-string.hh - string format tools ------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains define an internal helper class and a maccro to create
/// formated string
///
//===----------------------------------------------------------------------===//

#pragma once

#include <sstream>

namespace obcl {

/// Utils class to create a std::string, formatted the same way than streams
/// Shouldn't be used directly
/// Use the maccro FORMAT_STRING instead
class StringFormatter {
public:
  StringFormatter() = default;
  StringFormatter(const StringFormatter &) = delete;

  template <class T> StringFormatter &operator<<(const T &x) {
    _os << x;
    return *this;
  }

  std::string str() { return _os.str(); }

private:
  std::ostringstream _os;
};

} // namespace obcl

/// Maccro to create std::string with stream formatting (<<), in one line
/// @param CODE stream-like format expression
/// @returns formatted script
#define FORMAT_STRING(CODE) (((::obcl::StringFormatter() << CODE)).str())
