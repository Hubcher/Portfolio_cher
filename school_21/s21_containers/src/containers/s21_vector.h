#ifndef S21_CONTAINERS_VECTOR_H
#define S21_CONTAINERS_VECTOR_H

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  // Vector member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Public vector member functions
  vector() : arr(nullptr), size_(0), capacity_(0) {};
  explicit vector(size_type n)
      : arr(n > 0 ? new value_type[n] : nullptr), size_(n), capacity_(n) {};
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);      // copy constructor
  vector(vector &&v) noexcept;  // move constructor
  ~vector();
  vector &operator=(vector &&v) noexcept;

  // Public vector element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front() const;
  const_reference back() const;
  T *data();

  // Vector iterators
  iterator begin() const;
  iterator end() const;

  // Vector capacity
  bool empty() const;
  size_type size() const;
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  // Vector modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  value_type *arr;
  size_type size_;
  size_type capacity_;
};

};  // namespace s21

#endif
