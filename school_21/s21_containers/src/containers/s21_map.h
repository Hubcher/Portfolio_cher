#ifndef MAP_H
#define MAP_H
#include <cstddef>
#include <initializer_list>
#include <stack>
#include <stdexcept>
#include <utility>

template <typename Key, typename T>
class Map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  struct Node {
    value_type data;
    Node* left;
    Node* right;
    Node* parent;
    bool color;

    Node(const value_type& pair)
        : data(pair),
          left(nullptr),
          right(nullptr),
          parent(nullptr),
          color(true) {}
  };

  Map();
  Map(std::initializer_list<value_type> const& items);
  Map(const Map& m);
  Map(Map&& m) noexcept;
  ~Map();

  Map& operator=(Map&& m) noexcept;

  T& at(const Key& key);
  T& operator[](const Key& key);

  class iterator;
  class const_iterator;
  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void swap(Map& other);
  void merge(Map& other);

  bool contains(const Key& key) const;

 private:
  Node* root;
  size_type node_count;

  Node* insertNode(Node* root, Node* z);
  Node* findNode(const Key& key) const;
  void clearTree(Node* node);
  void fixInsertion(Node* z);
  void rotateLeft(Node*& root, Node*& x);
  void rotateRight(Node*& root, Node*& x);
};

#endif  // MAP_H
