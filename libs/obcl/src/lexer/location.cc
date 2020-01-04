#include "lexer/location.hh"
#include "lexer/stream.hh"
#include <cassert>

namespace obcl {

std::ostream &operator<<(std::ostream &os, const Location &loc) {

  if (!loc.begin.stream || !loc.end.stream) {
    os << "(End Of File)";
    return os;
  }

  os << loc.begin.stream->name() << ":";
  if (loc.begin.row == loc.end.row)
    os << loc.begin.row << ":" << loc.begin.col << "-" << loc.end.col;
  else
    os << loc.begin.row << "-" << loc.end.row << ":" << loc.begin.col << "-"
       << loc.end.col;
  return os;
}

void Location::pretty_print_code(std::ostream &os) const {

  // TODO: maby isn't possible
  if (!begin.stream || !end.stream || begin.stream != end.stream) {
    os << "[UNPRINTABLE CODE]" << std::endl;
    return;
  }

  for (std::size_t row = begin.row; row <= end.row; ++row) {
    auto line = begin.stream->extract_row(row);
    auto col_beg = row == begin.row ? begin.col : 1;
    auto col_end = row == end.row ? end.col : line.size();
    assert(col_beg > 0 && col_beg <= line.size());
    assert(col_end > 0 && col_end <= line.size());

    os << line << std::endl;
    for (std::size_t col = 1; col <= line.size(); ++col) {
      if (col >= col_beg && col <= col_end)
        os << '^';
      else
        os << ' ';
    }
    os << std::endl;
  }
}

} // namespace obcl
