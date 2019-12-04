//===-- utils/path.hh - path utils -----------------------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of several utils functions to manipulate
/// file paths.
/// It doesn't do any IO, just string manipulaitons
///
//===----------------------------------------------------------------------===//

#include <string>
#include <utility>
#include <vector>

namespace obcl {

namespace path {

/// @returns the name of the directory given a full file path
std::string dirname(const std::string &p);

/// @returns the name of a the file given the full path
std::string basename(const std::string &p);

/// Split a path at it's extension
std::pair<std::string, std::string> split_ext(const std::string &p);

} // namespace path

} // namespace obcl
