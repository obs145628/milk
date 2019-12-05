#include "utils/path.hh"

namespace {
constexpr char SEP = '/';
const char SEP_STR[] = {SEP, '\0'};
} // namespace

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

std::string join(const std::string &p1, const std::string &p2) {
  if (p1.empty())
    return p2;
  else if (p2.empty())
    return p1;
  if (p2.size() > 0 && p2.front() == SEP)
    return p2;
  if (p1.size() > 0 && p1.back() == SEP)
    return p1 + p2;
  else
    return p1 + SEP_STR + p2;
}

} // namespace path
} // namespace obcl
