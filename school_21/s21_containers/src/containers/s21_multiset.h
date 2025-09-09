#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <vector>

#include "s21_avl_tree.h"
namespace s21 {

template <typename Key>
class multiset {
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

  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms) noexcept;
  ~multiset();

  multiset<value_type>& operator=(multiset& s);
  multiset<value_type>& operator=(multiset&& ms) noexcept;

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  iterator insert(const value_type& value);
  void erase(iterator item);
  void swap(multiset& other);
  void merge(multiset& other);

  size_type count(const Key& key);
  iterator find(const Key& key);
  bool contains(const Key& key);

  std::pair<iterator, iterator> equal_range(const Key& key);
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);

  template <typename... Args>
  std::vector<typename multiset<Key>::iterator> insert_many(multiset<Key>& ms,
                                                            Args&&... args) {
    std::vector<typename multiset<Key>::iterator> v;
    (v.emplace_back(ms.insert(std::forward<Args>(args))), ...);
    return v;
  }
};
}  // namespace s21

#endif  // S21_MULTISET_H
