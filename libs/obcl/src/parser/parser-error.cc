#include "parser/parser-error.hh"
#include "lexer/location.hh"
#include "lexer/stream.hh"
#include <sstream>

namespace obcl {

ParserError::ParserError(const Location &loc, const std::string &mess) {
  std::ostringstream os;
  os << "Parser error at " << loc << "': " << mess << std::endl;
  loc.pretty_print_code(os);
  _str = os.str();
}

} // namespace obcl
