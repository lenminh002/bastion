#pragma once

template <typename T> class DoublyLinkedList {
  struct Node {
    T value;
    Node *prev;
    Node *next;

    Node(const T &value);
  };

  Node *head;
  Node *tail;
  int count;

public:
  DoublyLinkedList();
  DoublyLinkedList(const DoublyLinkedList<T> &other);
  DoublyLinkedList<T> &operator=(const DoublyLinkedList<T> &other);
  ~DoublyLinkedList() { clear(); }

  void pushFront(const T &value);
  void pushBack(const T &value);
  void removeAt(int index);
  void clear();

  T &front() { return head->value; }
  const T &front() const { return head->value; }
  T &back() { return tail->value; }
  const T &back() const { return tail->value; }

  T &operator[](int index) { return nodeAt(index)->value; }
  const T &operator[](int index) const { return nodeAt(index)->value; }

  int size() const { return count; }
  bool isEmpty() const { return count == 0; }

private:
  Node *nodeAt(int index) const;
};

template <typename T>
DoublyLinkedList<T>::Node::Node(const T &value)
    : value(value), prev(nullptr), next(nullptr) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &other)
    : head(nullptr), tail(nullptr), count(0) {
  Node *current = other.head;
  while (current != nullptr) {
    pushBack(current->value);
    current = current->next;
  }
}

template <typename T>
DoublyLinkedList<T> &
DoublyLinkedList<T>::operator=(const DoublyLinkedList<T> &other) {
  if (this == &other) {
    return *this;
  }

  clear();

  Node *current = other.head;
  while (current != nullptr) {
    pushBack(current->value);
    current = current->next;
  }

  return *this;
}

template <typename T> void DoublyLinkedList<T>::pushFront(const T &value) {
  Node *node = new Node(value);

  if (head == nullptr) {
    head = node;
    tail = node;
    count++;
    return;
  }

  node->next = head;
  head->prev = node;
  head = node;
  count++;
}

template <typename T> void DoublyLinkedList<T>::pushBack(const T &value) {
  Node *node = new Node(value);

  if (tail == nullptr) {
    head = node;
    tail = node;
    count++;
    return;
  }

  node->prev = tail;
  tail->next = node;
  tail = node;
  count++;
}

template <typename T> void DoublyLinkedList<T>::removeAt(int index) {
  if (index < 0 || index >= count) {
    return;
  }

  Node *target = nodeAt(index);

  if (target->prev != nullptr) {
    target->prev->next = target->next;
  } else {
    head = target->next;
  }

  if (target->next != nullptr) {
    target->next->prev = target->prev;
  } else {
    tail = target->prev;
  }

  delete target;
  count--;
}

template <typename T> void DoublyLinkedList<T>::clear() {
  Node *current = head;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }

  head = nullptr;
  tail = nullptr;
  count = 0;
}

// private helper
template <typename T>
typename DoublyLinkedList<T>::Node *
DoublyLinkedList<T>::nodeAt(int index) const {
  if (index < count / 2) {
    Node *current = head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }

    return current;
  }

  Node *current = tail;
  for (int i = count - 1; i > index; i--) {
    current = current->prev;
  }

  return current;
}
