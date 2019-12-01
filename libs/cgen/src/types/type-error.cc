#include "types/type-error.hh"
#include "ast/ast.hh"
#include "types/type-builder.hh"
#include "types/type.hh"

#include "obcl/utils/format-string.hh"

#include <sstream>

namespace cgen {

TypeError::TypeError(const AST &node, const std::string &method,
                     const std::string &mess) {
  std::ostringstream os;
  os << "Type error at " << node.loc() << "for " << method << std::endl;
  os << mess << std::endl;

  node.loc().pretty_print_code(os);
  _str = os.str();

  TypeBuilder::instance().dump_types();
}

TypeMismatchError::TypeMismatchError(const AST &node, const std::string &method,
                                     const Type *type_expect,
                                     const Type *type_act)
    : TypeError(node, method,
                FORMAT_STRING("Type '" << type_act->to_str()
                                       << "' cannot be matched to type '"
                                       << type_expect->to_str() << "'")) {}

} // namespace cgen
