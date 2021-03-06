#include "lexer/position.hh"
#include "lexer/stream.hh"

namespace obcl {

std::ostream &operator<<(std::ostream &os, const Position &pos) {
  os << pos.stream->name() << ":" << pos.row << ":" << pos.col;
  return os;
}

} // namespace obcl
