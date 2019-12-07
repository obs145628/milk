#include "utils/io.hh"
#include <unistd.h>

namespace obcl {

namespace utils {

bool is_file(const std::string &path) {
  return access(path.c_str(), F_OK) != -1;
}

} // namespace utils
} // namespace obcl
