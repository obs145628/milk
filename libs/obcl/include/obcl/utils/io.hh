//===-- utils/io.hh - io utils ----------------------------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of several utils functions for IO
/// operations on files
///
///
//===----------------------------------------------------------------------===//

#pragma once

#include <string>

namespace obcl {

namespace utils {

bool is_file(const std::string &path);

}

} // namespace obcl
