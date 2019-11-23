//===-- lexer/stream.hh - Stream struct definition --------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the struct Stream
///
//===----------------------------------------------------------------------===//

#pragma once

#include <cassert>
#include <istream>
#include <memory>

namespace obcl {

/// Wrapper around a generic buffered input stream
/// add some extra features:
/// - revert last read char
/// - get the actual column / row number
/// - extract some specific lines of code
/// - [TODO] extract a substring of the input given col/rows intervals
class Stream {

public:
  /// Create a new stream
  /// @param name - identifier, used to retrieve stream
  /// @pramm is - stream object, ownersgip given
  Stream(const std::string &name, std::unique_ptr<std::istream> &&is);

  Stream(const Stream &) = delete;
  Stream(Stream &&) = default;

  /// \returns identifier of the stream
  const std::string &name() const { return _name; }

  /// \returns 1-byte charachter at current position
  int get_char() const { return _char; }

  /// \returns current row number in input stream (starting at 1)
  std::size_t get_row() const { return _row; }

  /// \returns current column number in input stream (starting at 1)
  std::size_t get_col() const { return _col; }

  /// \returns current position in input stream (like ftell)
  std::size_t get_pos() const { return _pos; }

  /// move stream to the next char
  void next();

  /// move stream to the previous char
  /// cannot go back to older than one char
  void prev();

#if 0
  std::string extract_str(int pos_begin, int pos_end) {
    int len = pos_end - pos_begin;
    std::string res;
    res.resize(len);
    auto pos = _is->tellg();

    _is->clear();
    _is->seekg(pos_begin);
    _is->read(&res[0], len);

        _is->clear();
        _is->seekg(pos);
        return res;
      }

#endif

  /// Get the specific row
  /// Doesn't move the actual position
  /// Usually used to output messages
  std::string extract_row(std::size_t row);

private:
  enum class ReadState {
    FIRST_CHAR, // only one available char
    CURR_CHAR,  // at current char
    PREV_CHAR,  // at previous char (after calling prev())
  };

  std::string _name;
  std::unique_ptr<std::istream> _is;

  std::size_t _row;
  std::size_t _col;
  std::size_t _pos;
  std::size_t _prev_col; // needed to get to last call when prev() cancel
                         // newline
  ReadState _state;
  char _char;
  char _other; // previous or next char depending on _state
};

inline Stream::Stream(const std::string &name,
                      std::unique_ptr<std::istream> &&is)
    : _name(name), _is(std::move(is)), _row(1), _col(1), _pos(0),
      _state(ReadState::FIRST_CHAR), _char(is->get()) {}

inline void Stream::next() {
  auto curr_char = _char;
  if (curr_char == EOF)
    return;
  auto next_char = _state == ReadState::PREV_CHAR ? _other : _is->get();

  // upodate position
  _prev_col = _col;
  ++_pos;
  if (curr_char == '\n') {
    ++_row;
    _col = 1;
  } else {
    ++_col;
  }

  _state = ReadState::CURR_CHAR;
  _char = next_char;
  _other = curr_char;
}

inline void Stream::prev() {
  assert(_state == ReadState::CURR_CHAR);

  _state = ReadState::PREV_CHAR;
  std::swap(_char, _other);

  --_pos;
  if (_col == 1)
    --_row;
  _col = _prev_col;
}

inline std::string Stream::extract_row(std::size_t row) {
  std::string res;
  int cur = 1;
  auto pos = _is->tellg();
  _is->clear();
  _is->seekg(0);

  while (cur < row) {
    int c = _is->get();
    if (c == EOF)
      break;
    if (c == '\n')
      ++cur;
  }

  while (true) {
    int c = _is->get();
    if (c == EOF || c == '\n')
      break;
    res.push_back(c);
  }

  _is->clear();
  _is->seekg(pos);
  return res;
}

} // namespace obcl
