#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <iostream>

namespace s21 {
template <class T>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q) noexcept;
  ~queue();
  queue<value_type>& operator=(queue&& q) noexcept;

  const_reference front() const;
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue& other);

  void clear();

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  struct Node {
    value_type data;
    Node* next;

    Node(const value_type& value) : data(value), next(nullptr){};
  };

 private:
  Node* head;
  Node* tail;
  size_type queue_size;
};

}  // namespace s21

#endif  // S21_QUEUE_H
