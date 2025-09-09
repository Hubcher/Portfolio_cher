#ifndef S21_STACK_H
#define S21_STACK_H

#include <iostream>

#include "s21_vector.h"
namespace s21 {

template <typename T>
class stack : protected vector<T> {
 public:
  // Stack Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  // Stack Member functions
  stack() = default;
  stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);
  stack(stack&& s) noexcept;
  ~stack() = default;
  stack& operator=(stack&& s) noexcept;

  // Stack Element access
  const_reference top() const;

  // Stack Capacity
  bool empty() const;
  size_type size() const;

  // Stack Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack& other);

  // Insert many
  template <typename... Args>
  void insert_many_front(Args&&... args);
};

}  // namespace s21

#endif  // !S21_STACK_H
