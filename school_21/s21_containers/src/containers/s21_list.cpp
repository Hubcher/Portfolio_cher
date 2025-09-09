#include "s21_list.h"


namespace s21 {
template class List<int>;
template class List<bool>;
template class List<float>;
template class List<double>;

template <typename value_type>
List<value_type>::List() : head(nullptr), tail(nullptr), list_size(0) {}

template <typename value_type>
List<value_type>::List(size_type n)
    : head(nullptr), tail(nullptr), list_size(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename value_type>
List<value_type>::List(const List& l)
    : head(nullptr), tail(nullptr), list_size(0) {
  Node* current = l.head;
  while (current) {
    push_back(current->data);
    current = current->next;
  }
}

template <typename value_type>
List<value_type>::List(List&& l) noexcept
    : head(l.head), tail(l.tail), list_size(l.list_size) {
  l.head = nullptr;
  l.tail = nullptr;
  l.list_size = 0;
}

template <typename value_type>
List<value_type>::List(std::initializer_list<value_type> const& items)
    : head(nullptr), tail(nullptr), list_size(0) {
  for (const auto& item : items) {
    push_back(item);
  }
}

template <typename value_type>
List<value_type>::~List() {
  clear();
}

template <typename value_type>
List<value_type>& List<value_type>::operator=(List&& l) noexcept {
  if (this != &l) {
    clear();
    head = l.head;
    tail = l.tail;
    list_size = l.list_size;
    l.head = nullptr;
    l.tail = nullptr;
    l.list_size = 0;
  }
  return *this;
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::front()
    const {
  if (empty()) throw std::out_of_range("List is empty");
  return head->data;
}

template <typename value_type>
typename List<value_type>::const_reference List<value_type>::back()
    const {
  if (empty()) throw std::out_of_range("List is empty");
  return tail->data;
}

template <typename value_type>
bool List<value_type>::empty() const {
  return list_size == 0;
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::size() const {
  return list_size;
}

template <typename value_type>
typename List<value_type>::size_type List<value_type>::max_size() const {
  return std::numeric_limits<size_type>::max();
}

template <typename value_type>
void List<value_type>::clear() {
  while (head) {
    pop_front();
  }
}

template <typename value_type>
void List<value_type>::push_back(const_reference value) {
  Node* newNode = new Node(value);
  if (tail) {
    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
  } else {
    head = tail = newNode;
  }
  ++list_size;
}

template <typename value_type>
void List<value_type>::pop_back() {
  if (tail) {
    Node* temp = tail;
    if (tail->prev) {
      tail = tail->prev;
      tail->next = nullptr;
    } else {
      head = tail = nullptr;
    }
    delete temp;
    --list_size;
  }
}

template <typename value_type>
void List<value_type>::push_front(const_reference value) {
  Node* newNode = new Node(value);
  if (head) {
    head->prev = newNode;
    newNode->next = head;
    head = newNode;
  } else {
    head = tail = newNode;
  }
  ++list_size;
}

template <typename value_type>
void List<value_type>::pop_front() {
  if (head) {
    Node* temp = head;
    if (head->next) {
      head = head->next;
      head->prev = nullptr;
    } else {
      head = tail = nullptr;
    }
    delete temp;
    --list_size;
  }
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::insert(
    iterator pos, const_reference value) {
  Node* newNode = new Node(value);
  Node* current = pos.current;

  if (!current) {
    push_back(value);
    return iterator(tail);
  }

  newNode->next = current;
  newNode->prev = current->prev;

  if (current->prev) {
    current->prev->next = newNode;
  } else {
    head = newNode;
  }
  current->prev = newNode;

  ++list_size;
  return iterator(newNode);
}

template <typename value_type>
void List<value_type>::erase(iterator pos) {
  Node* current = pos.current;

  if (!current) return;

  if (current->prev) {
    current->prev->next = current->next;
  } else {
    head = current->next;
  }

  if (current->next) {
    current->next->prev = current->prev;
  } else {
    tail = current->prev;
  }

  delete current;
  --list_size;
}

template <typename value_type>
void List<value_type>::swap(List& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(list_size, other.list_size);
}

template <typename value_type>
void List<value_type>::splice(const_iterator pos, List& other) {
  if (this == &other || other.empty())
    return;  // Проверка на самосплайс и пустой список

  Node* current = const_cast<Node*>(pos.current);

  if (!current) {  // Если позиция — конец текущего списка
    if (tail) {
      tail->next = other.head;
      other.head->prev = tail;
    } else {
      head = other.head;
    }
    tail = other.tail;
  } else if (current == head) {  // Если позиция — начало текущего списка
    other.tail->next = head;
    head->prev = other.tail;
    head = other.head;
  } else {  // Если позиция — в середине текущего списка
    other.tail->next = current;
    other.head->prev = current->prev;
    current->prev->next = other.head;
    current->prev = other.tail;
  }

  list_size += other.list_size;
  other.head = other.tail = nullptr;
  other.list_size = 0;
}

template <typename value_type>
void List<value_type>::merge(List& other) {
  Node* current = head;
  Node* otherCurrent = other.head;

  while (current && otherCurrent) {
    if (otherCurrent->data < current->data) {
      Node* nextOther = otherCurrent->next;
      insert(iterator(current), otherCurrent->data);
      other.erase(iterator(otherCurrent));
      otherCurrent = nextOther;
    } else {
      current = current->next;
    }
  }

  while (otherCurrent) {
    Node* nextOther = otherCurrent->next;
    push_back(otherCurrent->data);
    other.erase(iterator(otherCurrent));
    otherCurrent = nextOther;
  }
}

template <typename value_type>
void List<value_type>::reverse() {
  Node* current = head;
  Node* temp = nullptr;

  while (current) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp) {
    tail = head;
    head = temp->prev;
  }
}

template <typename value_type>
void List<value_type>::unique() {
  if (!head) return;
  Node* current = head;
  while (current->next) {
    if (current->data == current->next->data) {
      erase(iterator(current->next));
    } else {
      current = current->next;
    }
  }
}

template <typename value_type>
void List<value_type>::sort() {
  if (!head) return;

  std::vector<value_type> temp;
  Node* current = head;

  while (current) {
    temp.push_back(current->data);
    current = current->next;
  }

  std::sort(temp.begin(), temp.end(), std::less<value_type>());

  current = head;
  for (const auto& item : temp) {
    current->data = item;
    current = current->next;
  }
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::begin() {
  return iterator(head);
}

template <typename value_type>
typename List<value_type>::iterator List<value_type>::end() {
  return iterator(nullptr);
}

template <typename T>
typename List<T>::const_iterator List<T>::const_begin() const {
  return const_iterator(head);
}

template <typename T>
typename List<T>::const_iterator List<T>::const_end() const {
  return const_iterator(tail->next);
};
};