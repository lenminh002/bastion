#pragma once

template <typename T> class SinglyLinkedList {
  struct Node {
    T value;
    Node *next;

    Node(const T &value);
  };

  Node *head;
  int count;

public:
  SinglyLinkedList();
  SinglyLinkedList(const SinglyLinkedList<T> &other);
  SinglyLinkedList<T> &operator=(const SinglyLinkedList<T> &other);
  ~SinglyLinkedList() { clear(); };

  void pushFront(const T &value);
  void pushBack(const T &value);
  void removeAt(int index);
  void clear();

  T &operator[](int index);
  const T &operator[](int index) const;

  int size() const { return count; }
  bool isEmpty() const { return count == 0; }
};

template <typename T>
SinglyLinkedList<T>::Node::Node(const T &value) : value(value), next(nullptr) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), count(0) {}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T> &other)
    : head(nullptr), count(0) {

  Node *current = other.head;
  while (current != nullptr) {
    pushBack(current->value);
    current = current->next;
  }
}

template <typename T>
SinglyLinkedList<T> &
SinglyLinkedList<T>::operator=(const SinglyLinkedList<T> &other) {
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

template <typename T> void SinglyLinkedList<T>::pushFront(const T &value) {
  Node *node = new Node(value);
  node->next = head;
  head = node;
  count++;
}

template <typename T> void SinglyLinkedList<T>::pushBack(const T &value) {
  Node *node = new Node(value);

  if (head == nullptr) {
    head = node;
    count++;
    return;
  }

  Node *current = head;
  while (current->next != nullptr) {
    current = current->next;
  }

  current->next = node;
  count++;
}

template <typename T> void SinglyLinkedList<T>::removeAt(int index) {
  if (index < 0 || index >= count) {
    return;
  }

  if (index == 0) {
    Node *oldHead = head;
    head = head->next;
    delete oldHead;
    count--;
    return;
  }

  Node *previous = head;
  for (int i = 0; i < index - 1; i++) {
    previous = previous->next;
  }

  Node *target = previous->next;
  previous->next = target->next;
  delete target;
  count--;
}

template <typename T> void SinglyLinkedList<T>::clear() {
  Node *current = head;
  while (current != nullptr) {
    Node *next = current->next;
    delete current;
    current = next;
  }

  head = nullptr;
  count = 0;
}

template <typename T> T &SinglyLinkedList<T>::operator[](int index) {
  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  return current->value;
}

template <typename T>
const T &SinglyLinkedList<T>::operator[](int index) const {
  Node *current = head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }

  return current->value;
}
