#include "utils/path.hh"

namespace {
constexpr char SEP = '/';
}

namespace obcl {

namespace path {

std::string dirname(const std::string &p) {
  auto psep = p.find_last_of(SEP);
  if (psep == std::string::npos)
    return ".";
  else
    return p.substr(0, psep);
}

std::string basename(const std::string &p) {
  auto psep = p.find_last_of(SEP);
  if (psep == std::string::npos)
    return p;
  else
    return p.substr(psep + 1);
}

std::pair<std::string, std::string> split_ext(const std::string &p) {
  auto dsep = p.find_last_of('.');
  if (dsep == std::string::npos)
    return {p, ""};
  else
    return {p.substr(0, dsep), p.substr(dsep)};
}

} // namespace path
} // namespace obcl
