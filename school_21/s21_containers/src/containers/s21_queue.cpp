#include "s21_queue.h"

namespace s21 {
template class queue<int>;

template <typename value_type>
queue<value_type>::queue() : head(nullptr), tail(nullptr), queue_size(0) {}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const& items)
    : head(nullptr), tail(nullptr), queue_size(0) {
  for (const value_type& item : items) {
    push(item);
  }
}

template <typename value_type>
queue<value_type>::queue(const queue& q)
    : head(nullptr), tail(nullptr), queue_size(0) {
  Node* current = q.head;
  while (current != nullptr) {
    push(current->data);
    current = current->next;
  }
}

template <typename value_type>
queue<value_type>::queue(queue&& q) noexcept
    : head(q.head), tail(q.tail), queue_size(q.queue_size) {
  q.head = nullptr;
  q.tail = nullptr;
  q.queue_size = 0;
}

template <typename value_type>
queue<value_type>::~queue() {
  clear();
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(queue&& q) noexcept {
  if (this != &q) {
    clear();

    head = q.head;
    tail = q.tail;
    queue_size = q.queue_size;

    q.head = nullptr;
    q.tail = nullptr;
    q.queue_size = 0;
  }
  return *this;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return head->data;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() const {
  if (empty()) {
    throw std::out_of_range("Queue is empty");
  }
  return tail->data;
}

template <typename value_type>
bool queue<value_type>::empty() const {
  return queue_size == 0;
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() const {
  return queue_size;
}

template <typename value_type>
void queue<value_type>::push(const_reference value) {
  Node* tempNode = new Node(value);
  if (!tempNode) {
    throw std::bad_alloc();
  }
  if (tail == nullptr) {
    head = tail = tempNode;
  } else {
    tail->next = tempNode;
    tail = tempNode;
  }
  ++queue_size;
}

template <typename value_type>
void queue<value_type>::pop() {
  if (head) {
    Node* temp = head;
    head = head->next;
    delete temp;
    --queue_size;
  }
}

template <typename value_type>
void queue<value_type>::swap(queue& other) {
  std::swap(this->head, other.head);
  std::swap(this->tail, other.tail);
  std::swap(this->queue_size, other.queue_size);
}

template <typename value_type>
void queue<value_type>::clear() {
  while (!empty()) {
    Node* temp = head;
    head = head->next;
    delete temp;
    --queue_size;
  }
  tail = nullptr;
}

}  // namespace s21
