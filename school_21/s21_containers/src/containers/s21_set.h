#ifndef S21_SET_H
#define S21_SET_H

#include <vector>

#include "s21_avl_tree.h"
namespace s21 {

template <typename Key>
class set {
 private:
  BinaryTree<Key, int> tree;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key, int>::iterator;
  using const_iterator = typename BinaryTree<Key, int>::const_iterator;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const& items);
  set(set& s);
  set(set&& s) noexcept;
  ~set();
  set<value_type>& operator=(set&& s) noexcept;

  set<value_type>& operator=(set& s);
  Key& operator*(iterator item) const;

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const Key& key);
  bool contains(const Key& key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    std::vector<std::pair<iterator, bool>> v;
    (v.emplace_back(insert(std::forward<Args>(args))), ...);
    return v;
  }
};
}  // namespace s21

#endif  // S21_SET_H