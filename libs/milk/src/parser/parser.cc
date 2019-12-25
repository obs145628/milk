#include "parser/parser.hh"

#include "ast/all.hh"
#include "parser/lexer.hh"

#include "obcl/parser/parser-error.hh"

#include <cassert>

using obcl::Token;

namespace milk {

Parser::Parser() : obcl::Parser(token_infos_custom), _ast(nullptr) {}

void Parser::parse_file(const std::string &path) {
  assert(!_ast.get());
  _lex.set_stream_file(path);
  _ast = _r_file();
}

void Parser::parse_string(const std::string &str) {
  assert(!_ast.get());
  _lex.set_stream_raw(str);
  _ast = _r_file();
}

// file: def+ @eof
ASTProgramPtr Parser::_r_file() {
  std::vector<ASTDefPtr> defs;
  while (_peek_any_of({TOK_KW_FN, TOK_KW_TYPE, TOK_KW_STRUCT, TOK_KW_ENUM}))
    defs.emplace_back(_r_def());
  _consume_of_type(obcl::TOK_EOF, "r:file");
  return std::make_unique<ASTProgram>(std::move(defs));
}

// def:   fundef
//     |  aliasef
//     |  structdef
//     |  enumdef
ASTDefPtr Parser::_r_def() {
  auto tok = _peek_token();
  switch (tok.type) {
  case TOK_KW_FN:
    return _r_fundef();
  case TOK_KW_TYPE:
    return _r_aliasdef();
  case TOK_KW_STRUCT:
    return _r_structdef();
  case TOK_KW_ENUM:
    return _r_enumdef();
  default:
    throw obcl::ParserError(tok.loc, "r:def invalid token");
  }
}

// fundef: 'fn' @id '(' <fundef_argslist> ')' ':' <typelabel> <stmt>
ASTDefFunPtr Parser::_r_fundef() {
  auto beg_tok = _consume_of_type(TOK_KW_FN, "r:fundef: expected keyword 'fn'");
  auto name = _consume_id("r:fundef: expected function name");
  _consume_of_type(TOK_SYM_LRBRAC, "r:fundef: expected '('");
  auto args = _r_fundef_argslist();
  _consume_of_type(TOK_SYM_RRBRAC, "r:fundef: expected ')'");
  _consume_of_type(TOK_SYM_COLON, "r:fundef: expected ':'");
  auto ret_type = _r_typelabel();
  auto body = _r_stmt();
  return std::make_unique<ASTDefFun>(beg_tok.loc, ASTDefFun::Kind::FUN, name,
                                     std::move(args), std::move(ret_type),
                                     std::move(body));
}

// fundef_argslist:  <fundef_arg> (',' <fundef_arg>)*
//		     | ((empty))
//
// fundef_arg: ['const'] @id ':' <typelabel>
ast_storage_list_t Parser::_r_fundef_argslist() {
  ast_storage_list_t res;
  bool has_coma = false;

  while (true) {
    if (!has_coma)
      _consume_of_type(TOK_SYM_RRBRAC,
                       "r_fundef_argslist: expected end of arguments ')'");

    auto beg_tok = obcl::Token::eof();
    bool is_const = _consume_if_type(TOK_KW_CONST, &beg_tok);
    auto name = _consume_of_type(obcl::TOK_ID,
                                 "r:fundef_argslist: exepected argument name");
    if (!is_const)
      beg_tok = name;
    _consume_of_type(TOK_SYM_COLON, "r:fundef_argslist: expected ':'");
    auto type = _r_typelabel();
    auto end_loc = type->loc();
    res.push_back(
        std::make_unique<ASTNamedStorage>(obcl::Location(beg_tok.loc, end_loc),
                                          name.val, is_const, std::move(type)));

    has_coma = _consume_if_type(TOK_SYM_COMA);
  }

  return res;
}

// aliasdef: 'type' @id '=' <typelabel> ';'
ASTDefAliasPtr Parser::_r_aliasdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_TYPE, "r_aliasdef: expected keyword 'type'");
  auto name = _consume_id("r_aliasdef: expected type alias name");
  _consume_of_type(TOK_SYM_EQ,
                   "r_aliasdef: expected symbol '=' after alias name");
  auto type = _r_typelabel();
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r_aliasdef: expected symbol ';' at the end of an alias definition");
  return std::make_unique<ASTDefAlias>(beg_tok.loc, end_tok.loc, name,
                                       std::move(type));
}

// structdef: 'struct' @id '{' <structdef_field>+ '}' ';'
ASTDefStructPtr Parser::_r_structdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_STRUCT, "r:structdef: expected keyword 'struct'");
  auto name = _consume_id("r:structdef: expected struct name");
  _consume_of_type(TOK_SYM_LCBRAC, "r:structdef: expected symbol '{'");

  ast_defs_list_t fields;
  while (!_consume_if_type(TOK_SYM_RCBRAC))
    fields.push_back(_r_structdef_field());

  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:structdef: expected symbol ';' at the end of a struct definition");
  return std::make_unique<ASTDefStruct>(beg_tok.loc, end_tok.loc, name,
                                        std::move(fields));
}

// structdef_field:   structdef_attr
//		     |  structdef_meth
ASTDefPtr Parser::_r_structdef_field() {
  auto tok = _peek_token();
  switch (tok.type) {
  case TOK_KW_LET:
  case TOK_KW_CONST:
    return _r_structdef_attr();
  case TOK_KW_FN:
    return _r_structdef_meth();
  default:
    throw obcl::ParserError(tok.loc, "r:structdef_field: invalid token");
  };
}

// structdef_attr:   'let'|'const' @id ':' <typelabel> ';'
ASTDefVarPtr Parser::_r_structdef_attr() {
  auto beg_tok =
      _consume_of_type({TOK_KW_LET, TOK_KW_CONST},
                       "r:structdef_attr: expected keyword 'let' or 'const'");
  bool is_const = beg_tok.type == TOK_KW_CONST;
  auto name = _consume_id("r:structdef_atrr: expected attr name");
  _consume_of_type(TOK_SYM_COLON, "r:structdef_attr: expected symbol ':'");
  auto type = _r_typelabel();
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:struct_attr: expected ';' at the end of struct attr definition");

  obcl::Location loc(beg_tok.loc, end_tok.loc);
  return std::make_unique<ASTDefVar>(
      loc, ASTDefVar::Kind::STRUCT_FIELD,
      std::make_unique<ASTNamedStorage>(loc, name, is_const, std::move(type)));
}

// structdef_meth: 'fn' @id '(' <fundef_argslist> ')' ['const'] ':'
// <typelabel> <stmt>
ASTDefFunPtr Parser::_r_structdef_meth() {
  auto beg_tok =
      _consume_of_type(TOK_KW_FN, "r:structdef_meth: expected keyword 'fn'");
  auto name = _consume_id("r:structdef_meth: expected method name");
  _consume_of_type(TOK_SYM_LRBRAC, "r:structdef_meth: expected '('");
  auto args = _r_fundef_argslist();
  _consume_of_type(TOK_SYM_RRBRAC, "r:structdef_meth: expected ')'");
  _consume_of_type(TOK_SYM_COLON, "r:structdef_meth: expected ':'");
  bool is_const = _consume_if_type(TOK_KW_CONST);
  auto ret_type = _r_typelabel();
  auto body = _r_stmt();
  return std::make_unique<ASTDefFun>(
      beg_tok.loc,
      is_const ? ASTDefFun::Kind::METH_CONST : ASTDefFun::Kind::METH, name,
      std::move(args), std::move(ret_type), std::move(body));
}

// enumdef: 'enum' @id [':' <typelabel>] '{' <enumdef_field>+ '}' ';'
//
// enumdef_field: @id ['=' @int] ';'
ASTDefEnumPtr Parser::_r_enumdef() {
  auto beg_tok =
      _consume_of_type(TOK_KW_ENUM, "r:enumdef: expected keyword 'enum'");
  auto name = _consume_id("r:enumdef: expected enum name");
  auto type = _consume_if_type(TOK_SYM_COLON)
                  ? _r_typelabel()
                  : std::make_unique<ASTTypeLabelName>(
                        beg_tok.loc, ASTDefEnum::DEF_TYPENAME);

  _consume_of_type(TOK_SYM_LCBRAC, "r:enumdef: expected symbol '{'");
  ASTDefEnum::fields_t fields;
  int next_val = 0;
  while (_peek_type() == obcl::TOK_ID) {
    auto name = _consume_id("r:enumdef: expected enum field name");
    int val =
        _consume_if_type(TOK_SYM_EQ)
            ? _consume_cint("r:enumdef: expected int for enum field value")
            : next_val;
    _consume_of_type(
        TOK_SYM_SEMI,
        "r:enumdef: expected symbol ';' at the end of an enum field");
    next_val = val + 1;
    fields.emplace_back(name, val);
  }

  _consume_of_type(TOK_SYM_RCBRAC, "r:enumdef: expected symbol '}'");
  auto end_tok = _consume_of_type(
      TOK_SYM_SEMI,
      "r:enumdef: expected symbol ';' at the end of enum definition");
  return std::make_unique<ASTDefEnum>(beg_tok.loc, end_tok.loc, name,
                                      std::move(type), fields);
}

// typelabel:   <valuetypelabel>
//	       | '&' <valuetypelabel>
//	       | '&const' <valuetypelabel>
//	       | '&[]' <valuetypelabel>
//	       | '&[]const' <valuetypelabel>
//
// valuetypelabel: @id
ASTTypeLabelPtr Parser::_r_typelabel() {

  auto beg_tok = _get_token();
  switch (beg_tok.type) {

  case obcl::TOK_ID:
    return std::make_unique<ASTTypeLabelName>(beg_tok);

  case TOK_SYM_MREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::MUT_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&'")));

  case TOK_SYM_CREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::CONST_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&const'")));

  case TOK_SYM_MAREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::MUT_ARR_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&[]'")));

  case TOK_SYM_CAREF:
    return std::make_unique<ASTTypeLabelRef>(
        beg_tok.loc, ASTTypeLabelRef::Kind::CONST_ARR_REF,
        std::make_unique<ASTTypeLabelName>(_consume_of_type(
            obcl::TOK_ID,
            "r:typelabel: expected type name after qualifier '&[]const'")));

  default:
    throw obcl::ParserError(beg_tok.loc, "r:typelabel invalid token");
  }
}

} // namespace milk
