#ifndef S21_AVL_TREE_H
#define S21_AVL_TREE_H

#include <iostream>
#include <limits>
#include <memory>
#include <utility>

namespace s21 {
template <typename Key, typename T>
class BinaryTree {
 private:
  struct Node {
    Node(Key k, T v)
        : key(k), value(v), parent(nullptr), left(nullptr), right(nullptr) {}

    Key key;
    T value;
    Node* parent = nullptr;
    std::unique_ptr<Node> left = nullptr;
    std::unique_ptr<Node> right = nullptr;
  };

  template <typename IteratorType>
  IteratorType getBegin() const {
    Node* node = root.get();
    while (node->left) {
      node = node->left.get();
    }
    return IteratorType(node);
  }

  template <typename IteratorType>
  IteratorType getFind(const Key& k) const {
    Node* current = root.get();
    while (current) {
      if (k < current->key) {
        current = current->left.get();
      } else if (current->key < k) {
        current = current->right.get();
      } else {
        return IteratorType(current);
      }
    }
    return IteratorType(nullptr);
  }

  size_t tree_size;

 public:
  class BaseIterator;
  class Iterator;
  class ConstIterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  class BaseIterator {
   public:
    BaseIterator(Node* node = nullptr) : current(node) {}

    bool operator==(const BaseIterator& other) const {
      return current == other.current;
    };

    bool operator!=(const BaseIterator& other) const {
      return current != other.current;
    };

    BaseIterator& operator++() {
      if (current) {
        if (current->right) {
          current = current->right.get();
          while (current->left) {
            current = current->left.get();
          }
        } else {
          Node* parent = current->parent;
          while (parent && current == parent->right.get()) {
            current = parent;
            parent = parent->parent;
          }
          current = parent;
        }
      }
      return *this;
    }

    Node* current;
  };

  class Iterator : public BaseIterator {
   public:
    using BaseIterator::BaseIterator;

    Key& operator*() const { return this->current->key; }
  };

  class ConstIterator : public BaseIterator {
   public:
    using BaseIterator::BaseIterator;

    std::pair<const Key&, const T&> operator*() const {
      return std::make_pair(this->current->key, this->current->value);
    }
  };

  std::unique_ptr<Node> root;

  BinaryTree() : tree_size(0), root(nullptr){};

  BinaryTree(BinaryTree& other) : BinaryTree() {
    for (const auto& item : other) {
      insert(item);
    }
  };

  BinaryTree(BinaryTree&& other) : BinaryTree() { swap(other); };

  ~BinaryTree() { clear(); };

  BinaryTree& operator=(BinaryTree other) {
    swap(other);
    return *this;
  }

  Iterator begin() {
    if (!root) {
      return end();
    }
    return getBegin<Iterator>();
  }

  ConstIterator begin() const {
    if (!root) {
      return end();
    }
    return getBegin<ConstIterator>();
  }

  Iterator end() { return Iterator(nullptr); }

  ConstIterator end() const { return ConstIterator(nullptr); }

  bool empty() const { return root == nullptr; }

  size_t size() const { return tree_size; };

  size_t max_size() const { return std::numeric_limits<size_t>::max(); }

  void clear() {
    root = nullptr;
    tree_size = 0;
  };

  std::pair<Iterator, bool> multiInsert(const Key key, T val) {
    return insert(key, val, true);
  }

  std::pair<Iterator, bool> insert(const std::pair<Key, T>& pair) {
    return insert(pair.first, pair.second);
  }

  std::pair<Iterator, bool> insert(Key k, T v, bool flag = false) {
    if (!root) {
      root = std::make_unique<Node>(k, v);
      ++tree_size;
      return std::make_pair(Iterator(root.get()), true);
    }
    Node* current = root.get();
    while (true) {
      if (k < current->key) {
        if (!current->left) {
          current->left = std::make_unique<Node>(k, v);
          current->left->parent = current;
          ++tree_size;
          return std::make_pair(Iterator(current->left.get()), true);
        }
        current = current->left.get();
      } else if (current->key < k || (current->key == k && flag)) {
        if (!current->right) {
          current->right = std::make_unique<Node>(k, v);
          current->right->parent = current;
          ++tree_size;
          return std::make_pair(Iterator(current->right.get()), true);
        }
        current = current->right.get();
      } else {
        return std::make_pair(Iterator(current), false);
      }
    }
  }

  void erase(const Key& k) {
    auto item = find(k);
    if (item != end()) {
      erase(item);
    }
  }

  void erase(iterator item) {
    if (item == end()) {
      throw std::invalid_argument("Cannot erase end iterator");
    }
    Node* current = item.current;
    if (current->left && current->right) {
      auto successor = ++item;
      std::swap(current->key, successor.current->key);
      current = successor.current;
    }
    Node* child = nullptr;
    if (current->left) {
      child = current->left.release();
    } else if (current->right) {
      child = current->right.release();
    }
    if (current->parent) {
      if (current->parent->left.get() == current) {
        current->parent->left.reset(child);
      } else {
        current->parent->right.reset(child);
      }
    } else {
      root.reset(child);
    }
    --tree_size;
  }

  void swap(BinaryTree& other) {
    std::swap(root, other.root);
    std::swap(tree_size, other.tree_size);
  };

  Iterator find(const Key& k) { return getFind<Iterator>(k); }

  ConstIterator find(const Key& k) const { return getFind<ConstIterator>(k); }

  size_t count(const Key& key) {
    size_t result = 0;
    if (find(key) != nullptr) {
      for (auto item = begin(); item != end(); ++item) {
        if ((*item) == key) {
          result++;
        }
      }
    }
    return result;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) {
    auto low = lower_bound(key);
    auto up = low;
    if (up != end() && *up == key) {
      up = upper_bound(key);
    }
    return std::make_pair(low, up);
  }

  Iterator lower_bound(const Key& key) {
    if (find(key) == nullptr) {
      return end();
    }
    return find(key);
  }

  Iterator upper_bound(const Key& key) {
    auto item = begin();
    for (; item != end(); ++item) {
      if ((*item) > key) {
        break;
      }
    }
    return item;
  }
};
}  // namespace s21

#endif  // S21_AVL_TREE_H
