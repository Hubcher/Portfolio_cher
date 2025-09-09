#include "s21_set.h"

namespace s21 {

template class set<int>;

template <typename Key>
set<Key>::set() : tree() {}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key>::set(set& s) {
  for (auto item = s.begin(); item != s.end(); ++item) {
    insert(*item);
  }
}

template <typename Key>
set<Key>::set(set&& s) noexcept : tree(std::move(s.tree)) {}

template <typename Key>
set<Key>::~set() {
  clear();
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& s) noexcept {
  if (this != &s) {
    tree = std::move(s.tree);
  }
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(set& s) {
  if (this != &s) {
    clear();
    for (auto item = s.begin(); item != s.end(); ++item) {
      insert(*item);
    }
  }
  return *this;
}

template <typename Key>
Key& set<Key>::operator*(iterator item) const {
  return item.current->key;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() {
  return tree.begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  return tree.end();
}

template <typename Key>
bool set<Key>::empty() {
  return tree.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() {
  return tree.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() {
  return tree.max_size();
}

template <typename Key>
void set<Key>::clear() {
  tree.clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  auto result = tree.insert(value, 0);
  return std::make_pair(iterator(result.first), result.second);
}

template <typename Key>
void set<Key>::erase(iterator item) {
  if (item == tree.end()) {
    throw std::out_of_range("Cannot erase end iterator");
  }
  tree.erase(item);
}

template <typename Key>
void set<Key>::swap(set& other) {
  tree.swap(other.tree);
}

template <typename Key>
void set<Key>::merge(set& other) {
  for (auto&& item : other) {
    insert(std::move(item));
  }
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return tree.find(key);
}

template <typename Key>
bool set<Key>::contains(const Key& key) {
  return tree.find(key) != tree.end();
}
} // namespace s21

