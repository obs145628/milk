//===-- utils/str.hh - string utils -----------------------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of several utils functions to manipulate
/// strings
///
//===----------------------------------------------------------------------===//

#include <string>
#include <vector>

namespace obcl {

namespace str {

/// Split a string, using the ',' separator
std::vector<std::string> split(const std::string &str);

} // namespace str
} // namespace obcl
