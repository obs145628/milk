#include "lexer/lexer.hh"
#include "lexer/lexer-error.hh"
#include "utils/debug.hh"
#include <fstream>
#include <sstream>

namespace {

bool is_wspace(char c) {
  return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool is_digit(char c) { return c >= '0' && c <= '9'; }

bool is_letter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_idchar(char c) {
  return is_letter(c) || (c >= '0' && c <= '9') || c == '_' || c == '$';
}

bool is_idword(const char *s) {
  if (!is_idchar(*s) || is_digit(*s))
    return false;
  ++s;

  for (; *s; ++s)
    if (!is_idchar(*s))
      return false;

  return true;
}

obcl::Position get_pos(obcl::Stream &is) {
  return obcl::Position(is.get_row(), is.get_col(), is.get_pos(), &is);
}

} // namespace

namespace obcl {

Lexer::Lexer(const CustomTokenInfos *custom)
    : _stream(nullptr), _peek(Token::null()) {

  for (; custom->type_id != 0; ++custom) {
    Token::add_type(custom->type_id, custom->repr);

    const char *word = custom->val;
    assert(*word);

    if (!is_idchar(*word)) {
      _trie_nonid.add_word(word, custom->type_id);
    }

    else if (is_idword(word)) {
      _custom_id.emplace(custom->val, custom->type_id);
    }

    else {
      PANIC("Invalid language definition: custom token '" + std::string(word) +
            "' is invalid");
    }
  }

  _trie_nonid.ready();
}

void Lexer::set_stream_file(const std::string &path) {
  // [TODO]: get abs_path
  std::string abs_path = path;

  auto fs = std::make_unique<std::ifstream>(abs_path);
  if (fs->fail())
    PANIC("Failed to open source file '" + path + "'");

  Stream is(abs_path, std::move(fs));
  _set_stream(std::make_unique<Stream>(std::move(is)));
}

void Lexer::set_stream_raw(const std::string &str) {
  static int raw_id = 1;
  std::string name = "(raw string:" + std::to_string(raw_id++) + ")";
  Stream is(name, std::make_unique<std::istringstream>(str));
  _set_stream(std::make_unique<Stream>(std::move(is)));
}

void Lexer::reset_stream() { _set_stream(nullptr); }

Token Lexer::peek_token() {
  _fetch_peek();
  return _peek;
}

Token Lexer::get_token() {
  Token res = peek_token();
  if (!res.is_eof())
    _peek = Token::null();
  return res;
}

bool Lexer::is_eof() {
  _fetch_peek();
  return _peek.type == TOK_EOF;
}

void Lexer::_fetch_peek() {
  if (!_peek.is_null())
    return;
  _peek = _read_token();
  assert(!_peek.is_null());
}

Token Lexer::_read_token() {

  // 1) no stream => EOF
  if (_stream.get() == nullptr)
    return Token::eof();
  Stream &is = *_stream;

  // 2) Skip whitespaces
  while (true) {
    int c = is.get_char();
    if (c == EOF)
      return Token::eof();
    if (!is_wspace(c))
      break;
    is.next();
  }

  // 3) Can find Lexer 'automaton mode' given the first char of the Token
  char start = is.get_char();
  bool can_id = is_idchar(start) && !is_digit(start);
  bool can_custom_nonidstart = _trie_nonid.can_start_with(start);

  // 4) redirect to the right method
  if (start == '\'' || start == '"')
    return _read_string();
  else if (is_digit(start))
    return _read_number();
  else if (can_custom_nonidstart) {
    return _read_custom_nonidstart();
  } else if (can_id) {
    return _read_id_or_custom_id();
  }

  // 5) Lexer error: invalid first char of Token
  auto err_pos = get_pos(is);
  throw LexerError(Location(err_pos, err_pos),
                   "Character is not a valid start of token");
}

Token Lexer::_read_string() {
  Stream &is = *_stream;
  char start = is.get_char();
  std::string val;
  Position begin = get_pos(is);
  is.next();
  val.push_back(start);
  bool escaped = false;

  while (true) {
    int c = is.get_char();
    if (c == EOF) {
      throw LexerError(Location(begin, get_pos(is)), "Unfinished string");
    }

    val.push_back(c);
    if (escaped)
      escaped = false;

    else {
      if (c == '\'' && c == start)
        break;
      else if (c == '"' && c == start)
        break;
      else if (c == '\\')
        escaped = true;
    }

    is.next();
  }

  Position end = get_pos(is);
  auto type = start == '\'' ? TOK_CONST_SQ : TOK_CONST_DQ;
  is.next();
  return Token(Location(begin, end), type, val);
}

Token Lexer::_read_number() {
  Stream &is = *_stream;
  std::string val;
  Position begin = get_pos(is);
  Position end = begin;
  bool dec = false;

  while (true) {
    int c = is.get_char();
    if ((c >= '0' && c <= '9') || (!dec && c == '.')) {
      if (c == '.')
        dec = true;
      val.push_back(c);
      end = get_pos(is);
      is.next();
    } else {
      break;
    }
  }

  return Token(Location(begin, end), dec ? TOK_CONST_FLOAT : TOK_CONST_INT,
               val);
}

Token Lexer::_read_custom_nonidstart() {

  Stream &is = *_stream;
  std::string val;
  Position begin = get_pos(is);
  Position last_pos = begin;
  token_type_t last_id = Trie::STATE_INVALID;

  _trie_nonid.reset();

  while (true) {
    char c = is.get_char();
    val.push_back(c);
    _trie_nonid.next(c);

    auto id = _trie_nonid.get_current_state();
    if (id != Trie::STATE_INVALID) {
      last_id = id;
      last_pos = get_pos(is);
    }

    if (!_trie_nonid.possible_word())
      break;

    is.next();
  }

  if (last_id == Trie::STATE_INVALID) {
    throw LexerError(Location(begin, get_pos(is)), "Invalid token");
  }

  size_t diff_pos = is.get_pos() - last_pos.pos;
  assert(diff_pos);
  if (diff_pos > 1) {
    //[TODO] should implement rollback to specific pos of lexer
    throw LexerError(Location(begin, get_pos(is)),
                     "Invalid token [rollback not implemented]");
  }

  val.resize(val.size() - diff_pos);
  return Token(Location(begin, last_pos), last_id, val);
}

Token Lexer::_read_id_or_custom_id() {
  Stream &is = *_stream;
  std::string val;
  Position begin = get_pos(is);
  Position end = begin;

  while (true) {
    int c = is.get_char();
    if (!is_idchar(c))
      break;

    val.push_back(c);
    end = get_pos(is);
    is.next();
  }

  auto it = _custom_id.find(val);
  auto tok_type = it != _custom_id.end() ? it->second : TOK_ID;
  return Token(Location(begin, end), tok_type, val);
}

void Lexer::_set_stream(std::unique_ptr<Stream> &&s) {
  std::unique_ptr<Stream> prev = std::move(_stream);
  _stream = std::move(s);
  if (prev.get())
    _old_streams.push_back(std::move(prev));
  _peek = Token::null();
}

} // namespace obcl
