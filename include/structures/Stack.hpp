#pragma once

#include "structures/ArrayList.hpp"

template <typename T> class Stack {
  ArrayList<T> items;

public:
  void push(const T &val) { items.pushBack(val); }

  T pop() {
    if (isEmpty()) {
      return T{};
    }
    T top = items[items.size() - 1];
    items.removeAt(items.size() - 1);
    return top;
  }

  T peek() const {
    if (isEmpty()) {
      return T{};
    }
    return items[items.size() - 1];
  }

  int size() const { return items.size(); }
  bool isEmpty() const { return items.isEmpty(); }
};
