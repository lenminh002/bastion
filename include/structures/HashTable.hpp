#pragma once

#include <string>

template <typename Value> class HashTable {
  struct Entry {
    std::string key;
    Value value;
    Entry *next;

    Entry(const std::string &key, const Value &value);
  };

  Entry **buckets;
  int bucketCount;
  int itemCount;

public:
  HashTable();
  HashTable(const HashTable<Value> &other);
  HashTable<Value> &operator=(const HashTable<Value> &other);
  ~HashTable();

  void insert(const std::string &key, const Value &value);
  bool contains(const std::string &key) const;
  Value *find(const std::string &key);
  const Value *find(const std::string &key) const;
  void clear();

  int size() const;
  bool isEmpty() const;

private:
  int bucketIndex(const std::string &key) const;
  unsigned long hashKey(const std::string &key) const;
  Entry *findEntry(const std::string &key) const;
  void initializeBuckets(int count);
  void copyFrom(const HashTable<Value> &other);
};

template <typename Value>
HashTable<Value>::Entry::Entry(const std::string &key, const Value &value)
    : key(key), value(value), next(nullptr) {}

template <typename Value> HashTable<Value>::HashTable() {
  initializeBuckets(8);
  itemCount = 0;
}

template <typename Value>
HashTable<Value>::HashTable(const HashTable<Value> &other) {
  initializeBuckets(other.bucketCount);
  itemCount = 0;
  copyFrom(other);
}

template <typename Value>
HashTable<Value> &HashTable<Value>::operator=(const HashTable<Value> &other) {
  if (this == &other) {
    return *this;
  }

  clear();
  delete[] buckets;

  initializeBuckets(other.bucketCount);
  itemCount = 0;
  copyFrom(other);

  return *this;
}

template <typename Value> HashTable<Value>::~HashTable() {
  clear();
  delete[] buckets;
}

template <typename Value>
void HashTable<Value>::insert(const std::string &key, const Value &value) {
  int index = bucketIndex(key);
  Entry *current = buckets[index];

  while (current != nullptr) {
    if (current->key == key) {
      current->value = value;
      return;
    }

    current = current->next;
  }

  Entry *entry = new Entry(key, value);
  entry->next = buckets[index];
  buckets[index] = entry;
  itemCount++;
}

template <typename Value>
bool HashTable<Value>::contains(const std::string &key) const {
  return findEntry(key) != nullptr;
}

template <typename Value> Value *HashTable<Value>::find(const std::string &key) {
  Entry *entry = findEntry(key);

  if (entry == nullptr) {
    return nullptr;
  }

  return &entry->value;
}

template <typename Value>
const Value *HashTable<Value>::find(const std::string &key) const {
  Entry *entry = findEntry(key);

  if (entry == nullptr) {
    return nullptr;
  }

  return &entry->value;
}

template <typename Value> void HashTable<Value>::clear() {
  for (int i = 0; i < bucketCount; i++) {
    Entry *current = buckets[i];

    while (current != nullptr) {
      Entry *next = current->next;
      delete current;
      current = next;
    }

    buckets[i] = nullptr;
  }

  itemCount = 0;
}

template <typename Value> int HashTable<Value>::size() const {
  return itemCount;
}

template <typename Value> bool HashTable<Value>::isEmpty() const {
  return itemCount == 0;
}

template <typename Value>
int HashTable<Value>::bucketIndex(const std::string &key) const {
  return static_cast<int>(hashKey(key) % bucketCount);
}

template <typename Value>
unsigned long HashTable<Value>::hashKey(const std::string &key) const {
  unsigned long hash = 0;

  for (char ch : key) {
    hash = hash * 31 + static_cast<unsigned char>(ch);
  }

  return hash;
}

template <typename Value>
typename HashTable<Value>::Entry *
HashTable<Value>::findEntry(const std::string &key) const {
  int index = bucketIndex(key);
  Entry *current = buckets[index];

  while (current != nullptr) {
    if (current->key == key) {
      return current;
    }

    current = current->next;
  }

  return nullptr;
}

template <typename Value> void HashTable<Value>::initializeBuckets(int count) {
  bucketCount = count;
  buckets = new Entry *[bucketCount];

  for (int i = 0; i < bucketCount; i++) {
    buckets[i] = nullptr;
  }
}

template <typename Value>
void HashTable<Value>::copyFrom(const HashTable<Value> &other) {
  for (int i = 0; i < other.bucketCount; i++) {
    Entry *current = other.buckets[i];

    while (current != nullptr) {
      insert(current->key, current->value);
      current = current->next;
    }
  }
}
