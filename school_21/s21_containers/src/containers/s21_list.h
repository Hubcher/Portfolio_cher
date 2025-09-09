#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace s21 {
template <typename T>
class List {
 private:
  struct Node {
    T data;
    Node* next;
    Node* prev;
    Node(const T& value = T(), Node* next_ptr = nullptr,
         Node* prev_ptr = nullptr)
        : data(value), next(next_ptr), prev(prev_ptr) {}
  };

  Node* head;
  Node* tail;
  size_t list_size;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  class iterator {
   public:
    Node* current;
    iterator(Node* node) : current(node) {}
    reference operator*() { return current->data; }

    iterator& operator++() {
      current = current->next;
      return *this;
    }

    iterator operator++(int) {
      iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator!=(const iterator& other) const {
      return current != other.current;
    }
  };

  class const_iterator {
   public:
    const Node* current;
    const_iterator(const Node* node) : current(node) {}

    const_iterator(const iterator& it) : current(it.current) {}

    const_reference operator*() const { return current->data; }

    const_iterator& operator++() {
      current = current->next;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    bool operator!=(const const_iterator& other) const {
      return current != other.current;
    }
    const typename List<T>::Node* getConstNode() { return current; }
  };

  List();
  List(size_type n);
  List(std::initializer_list<value_type> const& items);
  List(const List& l);
  List(List&& l) noexcept;
  ~List();

  List& operator=(List&& l) noexcept;

  const_reference front() const;
  const_reference back() const;

  iterator begin();
  iterator end();
  const_iterator const_begin() const;
  const_iterator const_end() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(List& other);
  void merge(List& other);
  void splice(const_iterator pos, List& other);
  void reverse();
  void unique();
  void sort();

  // insert_many
  template <typename... Args>
  typename List<T>::iterator insert_many(const_iterator pos, Args&&... args) {
    iterator i(const_cast<Node*>(pos.getConstNode()));
    for (const auto& arg : {args...}) {
      insert(i, arg);
    }
    return i;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    insert_many(const_end(), std::forward<Args>(args)...);
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    insert_many(const_begin(), std::forward<Args>(args)...);
  }
};
};  // namespace s21
#endif  // LIST_H