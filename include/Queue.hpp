#pragma once

#include <iostream>
template <typename T> class Queue {

private:
  T *data;
  int front;
  int rear;
  int capacity;
  int count;

public:
  Queue();
  ~Queue() { delete[] data; };
  Queue(const Queue<T> &other);
  Queue<T> &operator=(const Queue<T> &other);

  void enqueue(T val);
  T dequeue();

  T peek() const;
  int size() const { return count; }
  bool isEmpty() const { return count == 0; }

  const T &operator[](int index) const {
    return data[(front + index) % capacity];
  }
  T &operator[](int index) { return data[(front + index) % capacity]; }
};
// functions
template <typename T> Queue<T>::Queue() {
  capacity = 4;
  data = new T[capacity];
  front = 0;
  rear = 0;
  count = 0;
}

template <typename T> Queue<T>::Queue(const Queue<T> &other) {
  count = other.count;
  capacity = other.capacity;
  data = new T[capacity];
  front = other.front;
  rear = other.rear;

  for (int i = 0; i < capacity; i++) {
    data[i] = other.data[i];
  }
}

template <typename T> Queue<T> &Queue<T>::operator=(const Queue<T> &other) {
  if (this == &other) {
    return *this;
  }
  delete[] data;
  capacity = other.capacity;
  count = other.count;
  front = other.front;
  rear = other.rear;

  data = new T[capacity];

  for (int i = 0; i < capacity; i++) {
    data[i] = other.data[i];
  }

  return *this;
}

template <typename T> void Queue<T>::enqueue(T val) {
  if (count == capacity) {
    // resize
    T *newData = new T[capacity * 2];

    int oldIndex = front;
    for (int i = 0; i < count; i++) {
      newData[i] = data[oldIndex];
      oldIndex = (oldIndex + 1) % capacity;
    }

    delete[] data;
    data = newData;
    front = 0;
    rear = count;
    capacity *= 2;
  }

  data[rear] = val;
  rear = (rear + 1) % capacity;
  count++;
}

template <typename T> T Queue<T>::dequeue() {

  if (isEmpty()) {
    std::cout << "queue is empty, cannot dequeue" << std::endl;
    return T{};
  }

  T frontElement = data[front];

  front = (front + 1) % capacity;
  count--;

  return frontElement;
}

template <typename T> T Queue<T>::peek() const {
  if (isEmpty()) {
    std::cout << "queue is empty, cannot peek" << std::endl;
    return T{};
  }

  return data[front];
}
