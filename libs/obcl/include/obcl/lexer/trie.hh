//===-- lexer/trie.hh - Trie class definition ----------------*- C++ -*-===//
//
// OBCL compilers library
// Author: Steven Lariau
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the class Trie
///
//===----------------------------------------------------------------------===//

#pragma once

#include "fwd.hh"
#include <memory>

namespace obcl {

/// Trie data structure
/// Used by the lexer to recognise fixed words of the language
/// It's used for keywords, operators, or other static symbols
///
/// The first ste is to add all possible words in the trie
///
/// Then, when running the lexer, we call next(c) iteratively, passing chars of
/// After each call to next, it can be on 3 possible states:
/// The actual token form a word of the trie
/// The actual token is on the trie, adding other chars could lead to a word
/// The actual token cannot form a word of the trie
class Trie {
public:
  static constexpr token_type_t STATE_INVALID = -1;

  Trie();

  /// Add a new word to the trie
  /// Can only be called before calling ready
  void add_word(const char *w, token_type_t id);

  /// Must be called after every word is added
  /// It will optimise the trie, make it read-only, and go in query mode
  void ready();

  bool is_ready() const { return _ready; }

  void reset();

  void next(char c);

  /// @returns true if the possible state could lead to a word on the trie
  bool possible_word() const;

  /// @return the type id of the matched word
  /// Or STATE_INVALID if no word matched
  token_type_t get_current_state();

  /// @return if there is a word in the trie starting by \p c
  /// Ignore the current state
  bool can_start_with(char c) const;

private:
  bool _ready;

  struct RawTrie {
    char c;
    token_type_t val;
    std::unique_ptr<RawTrie> son;  /// first son
    std::unique_ptr<RawTrie> sibl; // left sibling
  };

  std::unique_ptr<RawTrie> _root;

  const RawTrie *_ptr;
};

} // namespace obcl
