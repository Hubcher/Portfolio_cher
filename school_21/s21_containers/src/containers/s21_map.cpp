#include "s21_map.h"

template class Map<int, char>;
template class Map<int, std::string>;

template <typename Key, typename T>
Map<Key, T>::Map() : root(nullptr), node_count(0) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) : Map() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& m) : Map() {
  for (auto it = m.begin(); it != m.end(); ++it) {
    insert(*it);
  }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map&& m) noexcept : root(m.root), node_count(m.node_count) {
  m.root = nullptr;
  m.node_count = 0;
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
  clear();
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map&& m) noexcept {
  if (this != &m) {
    clear();
    root = m.root;
    node_count = m.node_count;
    m.root = nullptr;
    m.node_count = 0;
  }
  return *this;
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
  clearTree(root);
  root = nullptr;
  node_count = 0;
}

template <typename Key, typename T>
void Map<Key, T>::clearTree(Node* node) {
  if (node) {
    clearTree(node->left);
    clearTree(node->right);
    delete node;
  }
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
  Node* node = findNode(key);
  if (!node) {
    throw std::out_of_range("Key not found in map");
  }
  return node->data.second;
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
  auto [it, inserted] = insert(std::make_pair(key, T()));
  return it->second;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const value_type& value) {
  Node* z = new Node(value);
  root = insertNode(root, z);
  fixInsertion(z);
  ++node_count;
  return {iterator(z), true};
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::findNode(const Key& key) const {
  Node* current = root;
  while (current) {
    if (key < current->data.first) {
      current = current->left;
    } else if (key > current->data.first) {
      current = current->right;
    } else {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename T>
bool Map<Key, T>::empty() const {
  return node_count == 0;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() const {
  return node_count;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() const {
  return static_cast<size_type>(-1);
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) const {
  return findNode(key) != nullptr;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  auto [it, inserted] = insert(std::make_pair(key, obj));
  if (!inserted) {
    it->second = obj;
  }
  return {it, true};
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(
    const Key& key, const T& obj) {
  Node* newNode = new Node(std::make_pair(key, obj));
  Node* current = root;
  Node* parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->data.first) {
      current = current->left;
    } else if (key > current->data.first) {
      current = current->right;
    } else {
      delete newNode;
      return {iterator(current), false};
    }
  }

  newNode->parent = parent;
  if (!parent) {
    root = newNode;
  } else if (key < parent->data.first) {
    parent->left = newNode;
  } else {
    parent->right = newNode;
  }

  fixInsertion(newNode);
  ++node_count;
  return {iterator(newNode), true};
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
  std::swap(root, other.root);
  std::swap(node_count, other.node_count);
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
  for (auto it = other.begin(); it != other.end();) {
    auto [insertedIt, inserted] =
        insert(std::move(it->first), std::move(it->second));
    if (inserted) {
      ++it;
    } else {
      ++it;
    }
  }
}

template <typename Key, typename T>
class Map<Key, T>::iterator {
 public:
  iterator() : current(nullptr) {}
  iterator(Node* node) : current(node) {}

  value_type& operator*() const { return current->data; }
  value_type* operator->() const { return &(current->data); }

  iterator& operator++();
  bool operator==(const iterator& other) const {
    return current == other.current;
  }
  bool operator!=(const iterator& other) const {
    return current != other.current;
  }

  iterator operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
  }

  Node* getCurrentNode() const { return current; }

 private:
  Node* current;
};

template <typename Key, typename T>
class Map<Key, T>::const_iterator {
 public:
  const_iterator() : node_ptr(nullptr) {}
  const_iterator(const Node* node) : node_ptr(node) {}

  const value_type& operator*() const { return node_ptr->data; }
  const value_type* operator->() const { return &(node_ptr->data); }

  const_iterator& operator++();
  bool operator==(const const_iterator& other) const {
    return node_ptr == other.node_ptr;
  }
  bool operator!=(const const_iterator& other) const {
    return node_ptr != other.node_ptr;
  }

 private:
  const Node* node_ptr;
};

template <typename Key, typename T>
typename Map<Key, T>::iterator& Map<Key, T>::iterator::operator++() {
  if (current == nullptr) return *this;

  if (current->right) {
    current = current->right;
    while (current->left) {
      current = current->left;
    }
  } else {
    Node* parent = current->parent;
    while (parent && current == parent->right) {
      current = parent;
      parent = parent->parent;
    }
    current = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator&
Map<Key, T>::const_iterator::operator++() {
  if (node_ptr == nullptr) {
    return *this;
  }

  if (node_ptr->right) {
    node_ptr = node_ptr->right;
    while (node_ptr->left) {
      node_ptr = node_ptr->left;
    }
  } else {
    const Node* parent = node_ptr->parent;
    while (parent && node_ptr == parent->right) {
      node_ptr = parent;
      parent = parent->parent;
    }
    node_ptr = parent;
  }
  return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
  Node* node = root;
  if (node) {
    while (node->left) {
      node = node->left;
    }
  }
  return iterator(node);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::begin() const {
  const Node* node = root;
  if (node) {
    while (node->left) {
      node = node->left;
    }
  }
  return const_iterator(node);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
  return iterator(nullptr);
}

template <typename Key, typename T>
typename Map<Key, T>::const_iterator Map<Key, T>::end() const {
  return const_iterator(nullptr);
}

template <typename Key, typename T>
typename Map<Key, T>::Node* Map<Key, T>::insertNode(Node* root, Node* z) {
  Node* parent = nullptr;
  Node* current = root;

  while (current) {
    parent = current;
    if (z->data.first < current->data.first) {
      current = current->left;
    } else if (z->data.first > current->data.first) {
      current = current->right;
    } else {
      return root;
    }
  }

  z->parent = parent;
  if (!parent) {
    root = z;
  } else if (z->data.first < parent->data.first) {
    parent->left = z;
  } else {
    parent->right = z;
  }

  return root;
}

template <typename Key, typename T>
void Map<Key, T>::rotateLeft(Node*& root, Node*& x) {
  Node* y = x->right;
  x->right = y->left;
  if (y->left != nullptr) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename Key, typename T>
void Map<Key, T>::rotateRight(Node*& root, Node*& x) {
  Node* y = x->left;
  x->left = y->right;
  if (y->right != nullptr) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

template <typename Key, typename T>
void Map<Key, T>::fixInsertion(Node* z) {
  while (z != root && z->parent->color == true) {
    Node* grandparent = z->parent->parent;
    if (z->parent == grandparent->left) {
      Node* uncle = grandparent->right;
      if (uncle && uncle->color == true) {
        z->parent->color = false;
        uncle->color = false;
        grandparent->color = true;
        z = grandparent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(root, z);
        }
        z->parent->color = false;
        grandparent->color = true;
        rotateRight(root, grandparent);
      }
    } else {
      Node* uncle = grandparent->left;
      if (uncle && uncle->color == true) {
        z->parent->color = false;
        uncle->color = false;
        grandparent->color = true;
        z = grandparent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(root, z);
        }
        z->parent->color = false;
        grandparent->color = true;
        rotateLeft(root, grandparent);
      }
    }
  }
  root->color = false;
}