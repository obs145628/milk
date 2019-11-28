//===--ast/ast-expr-string.hh - ASTExprString class definition ---------------*-
// C++ -*-===//
//
// cgen representation compiler library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class ASTExprString
///
//===----------------------------------------------------------------------===//

#pragma once

#include "ast-expr.hh"
#include "ast-visitor.hh"
#include <stdexcept>
#include <string>

namespace cgen {

/// AST node definition for a string constant expression
/// [TODO] May be removed in the future
class ASTExprString : public ASTExpr {

public:
  ASTExprString(const obcl::Location &loc, const std::string &val)
      : ASTExpr(loc), _val(val) {}

  void accept(ASTVisitor &visitor) const override { visitor.visit(*this); }

  const std::string &val() const { return _val; }

  // encode the string to be displayed (add '\')
  static std::string encode(const std::string &s) {
    std::string res;
    for (const auto &c : s) {
      if (c == '\n')
        res += "\\n";
      else if (c == '\t')
        res += "\\c";
      else if (c == '\\')
        res += "\\\\";
      else if (c == '"')
        res += "\\\"";
      else
        res.push_back(c);
    }
    return res;
  }

  // reverse the encode function
  static std::string decode(const std::string &s) {
    std::string res;
    bool esc = false;

    for (const auto &c : s) {
      if (!esc && c == '\\') {
        esc = true;
        continue;
      }

      if (esc) {
        if (c == 'n')
          res.push_back('\n');
        else if (c == 't')
          res.push_back('\t');
        else if (c == '\\')
          res.push_back('\\');
        else if (c == '"')
          res.push_back('"');
        else
          throw std::runtime_error{"Invalid escape sequence"};
      } else
        res.push_back(c);

      esc = false;
    }

    if (esc)
      throw std::runtime_error{"Infinished escape sequence"};
    return res;
  }

private:
  std::string _val;
};

} // namespace cgen
