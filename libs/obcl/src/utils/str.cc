#include "utils/str.hh"
#include <sstream>

namespace obcl {

namespace str {

std::vector<std::string> split(const std::string &str, char sep) {
  std::vector<std::string> res;
  std::istringstream is(str);
  std::string val;
  while (std::getline(is, val, sep))
    res.push_back(val);
  return res;
}

} // namespace str
} // namespace obcl
