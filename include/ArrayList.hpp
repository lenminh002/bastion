#pragma once

template <typename T> class ArrayList {
  int capacity;
  int count;
  T *data;

public:
  ArrayList();

  // copy constructor
  ArrayList(const ArrayList &other);

  // copy assignment operator
  ArrayList<T> &operator=(const ArrayList &other);

  ~ArrayList() { delete[] data; };

  void pushBack(const T &val);
  bool isEmpty() const { return count == 0; }
  int size() const { return count; }
  void removeAt(int index);

  const T &operator[](int index) const { return data[index]; };
  T &operator[](int index) { return data[index]; };
};

// functions
template <typename T> ArrayList<T>::ArrayList() {
  capacity = 10;
  count = 0;
  data = new T[capacity];
}

template <typename T> ArrayList<T>::ArrayList(const ArrayList &other) {
  capacity = other.capacity;
  count = other.count;
  data = new T[capacity];
  for (int i = 0; i < count; i++) {
    data[i] = other.data[i];
  }
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other) {
  if (this == &other) {
    return *this;
  }
  delete[] data;
  capacity = other.capacity;
  count = other.count;
  data = new T[capacity];
  for (int i = 0; i < count; i++) {
    data[i] = other.data[i];
  }
  return *this;
}

template <typename T> void ArrayList<T>::pushBack(const T &val) {
  if (count == capacity) {
    // resize data
    T *newData = new T[capacity * 2];
    for (int i = 0; i < count; i++) {
      newData[i] = data[i];
    }
    delete[] data;
    data = newData;
    capacity *= 2;
  }
  data[count] = val;
  count++;
}

template <typename T> void ArrayList<T>::removeAt(int index) {
  if (index < 0 || index >= count) {
    return;
  }

  for (int i = index; i < count - 1; i++) {
    data[i] = data[i + 1];
  }

  count--;
}
