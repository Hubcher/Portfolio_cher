#include "s21_stack.h"

namespace s21 {

// Stack Member functions

template class stack<int>;
template class stack<double>;


template <typename T>
stack<T>::stack(std::initializer_list<value_type> const& items)
    : vector<T>(items) {}

template <typename T>
stack<T>::stack(const stack& s) : vector<T>(s) {}

template <typename T>
stack<T>::stack(stack&& s) noexcept : vector<T>(std::move(s)) {}

template <typename T>
stack<T>& stack<T>::operator=(stack&& s) noexcept {
  if (this != &s) {
    vector<T>::operator=(std::move(s));
  }
  return *this;
}

// Stack Element access
template <typename T>
typename stack<T>::const_reference stack<T>::top() const {
  if (this->empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return this->back();  // Последний элемент вектора - это верх стека
}

// Stack Capacity
template <typename T>
bool stack<T>::empty() const {
  return vector<T>::empty();
}

template <typename T>
typename stack<T>::size_type stack<T>::size() const {
  return vector<T>::size();
}

// Stack Modifiers
template <typename T>
void stack<T>::push(const_reference value) {
  vector<T>::push_back(value);
}

template <typename T>
void stack<T>::pop() {
  if (this->empty()) {
    throw std::out_of_range("Stack is empty");
  }
  this->vector<T>::pop_back();
}

template <typename T>
void stack<T>::swap(stack& other) {
  vector<T>::swap(other);
}

// Insert many

template <typename T>
template <typename... Args>
void stack<T>::insert_many_front(Args&&... args) {
  vector<T>::insert_many_back(args...);
}

}  // namespace s21
