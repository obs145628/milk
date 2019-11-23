#include "lexer-error.hh"
#include <sstream>

namespace obcl {

LexerError::LexerError(const Location &loc, const std::string &mess) {
  std::ostringstream os;
  os << "Lexer error at " << loc << "': " << mess << std::endl;
  loc.pretty_print_code(os);
  _str = os.str();
}

} // namespace obcl
