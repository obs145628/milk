#include <cassert>
#include <lexer/trie.hh>

namespace obcl {

Trie::Trie()
    : _ready(false), _root(std::make_unique<RawTrie>()), _ptr(_root.get()) {
  _root->val = STATE_INVALID;
  _root->son = nullptr;
  _root->sibl = nullptr;
}

void Trie::add_word(const char *w, token_type_t id) {

  auto node = _root.get();
  for (; *w != '\0'; ++w) {
    char c = *w;
    if (!node->son) {
      node->son = std::make_unique<RawTrie>();
      node = node->son.get();
      node->c = c;
      node->val = STATE_INVALID;
      node->son = nullptr;
      node->sibl = nullptr;
      continue;
    }

    node = node->son.get();
    while (node->sibl) {
      if (node->c == c)
        break;
      node = node->sibl.get();
    }
    if (node->c == c) {
      continue;
    }

    node->sibl = std::make_unique<RawTrie>();
    node = node->sibl.get();
    node->c = c;
    node->val = STATE_INVALID;
    node->son = nullptr;
    node->sibl = nullptr;
  }

  node->val = id;
}

void Trie::ready() {
  assert(!_ready);
  _ready = true;
}

void Trie::reset() {
  assert(_ready);
  _ptr = _root.get();
}

void Trie::next(char c) {
  assert(_ready);
  if (!_ptr)
    return;

  const RawTrie *next = _ptr->son.get();
  while (next) {
    if (next->c == c)
      break;
    next = next->sibl.get();
  }
  _ptr = next;
}

bool Trie::possible_word() const {
  assert(_ready);
  return _ptr != nullptr;
}

token_type_t Trie::get_current_state() {
  assert(_ready);
  return _ptr ? _ptr->val : STATE_INVALID;
}

bool Trie::can_start_with(char c) const {
  const RawTrie *node = _root->son.get();
  while (node) {
    if (node->c == c)
      return true;
    node = node->sibl.get();
  }

  return false;
}

} // namespace obcl
