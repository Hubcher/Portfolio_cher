#include "s21_multiset.h"
namespace s21 {
template class multiset<int>;

template <typename Key>
multiset<Key>::multiset() : tree() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& ms) {
  std::pair<Key, int> pair;
  for (auto item = ms.begin(); item != ms.end(); ++item) {
    pair = *item;
    insert(pair.first);
  }
}

template <typename Key>
multiset<Key>::multiset(multiset&& ms) noexcept : tree(std::move(ms.tree)) {}

template <typename Key>
multiset<Key>::~multiset() {
  clear();
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset& s) {
  if (this != &s) {
    for (auto item = s.begin(); item != s.end(); ++item) {
      insert(*item);
    }
  }
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) noexcept {
  if (this != &ms) {
    tree = std::move(ms.tree);
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return tree.begin();
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::begin() const {
  return tree.begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return tree.end();
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::end() const {
  return tree.end();
}

template <typename Key>
bool multiset<Key>::empty() {
  return tree.empty();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() {
  return tree.size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() {
  return tree.max_size();
}

template <typename Key>
void multiset<Key>::clear() {
  tree.clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  auto result = tree.multiInsert(value, 0);
  return iterator(result.first);
}

template <typename Key>
void multiset<Key>::erase(iterator item) {
  if (item == tree.end()) {
    throw std::out_of_range("Cannot erase end iterator");
  }
  tree.erase(item);
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  tree.swap(other.tree);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  for (auto&& item : other) {
    insert(std::move(item));
  }
  other.clear();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) {
  return tree.count(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  return tree.find(key);
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) {
  return tree.find(key) != tree.end();
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return tree.equal_range(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  return tree.lower_bound(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return tree.upper_bound(key);
}

} // namespace s21

