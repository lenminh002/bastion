#pragma once

#include "structures/ArrayList.hpp"

template <typename Key, typename Value> class BinarySearchTree {
  struct Node {
    Key key;
    Value value;
    Node *left;
    Node *right;

    Node(const Key &key, const Value &value);
  };

  Node *root;
  int count;

public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree<Key, Value> &other);
  BinarySearchTree<Key, Value> &
  operator=(const BinarySearchTree<Key, Value> &other);
  ~BinarySearchTree();

  void insert(const Key &key, const Value &value);
  bool contains(const Key &key) const;
  Value *find(const Key &key);
  const Value *find(const Key &key) const;
  void keysInOrder(ArrayList<Key> &keys) const;
  void clear();

  int size() const;
  bool isEmpty() const;

private:
  Node *insertNode(Node *current, const Key &key, const Value &value,
                   bool &addedNewNode);
  Node *findNode(Node *current, const Key &key) const;
  void keysInOrder(Node *current, ArrayList<Key> &keys) const;
  Node *copyTree(Node *current);
  void clear(Node *current);
};

// definitions
template <typename Key, typename Value>
BinarySearchTree<Key, Value>::Node::Node(const Key &key, const Value &value)
    : key(key), value(value), left(nullptr), right(nullptr) {}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root(nullptr), count(0) {}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(
    const BinarySearchTree<Key, Value> &other)
    : root(nullptr), count(other.count) {
  root = copyTree(other.root);
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value> &BinarySearchTree<Key, Value>::operator=(
    const BinarySearchTree<Key, Value> &other) {
  if (this == &other) {
    return *this;
  }

  clear();
  root = copyTree(other.root);
  count = other.count;
  return *this;
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
  clear();
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const Key &key, const Value &value) {
  bool addedNewNode = false;
  root = insertNode(root, key, value, addedNewNode);

  if (addedNewNode) {
    count++;
  }
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::contains(const Key &key) const {
  return findNode(root, key) != nullptr;
}

template <typename Key, typename Value>
Value *BinarySearchTree<Key, Value>::find(const Key &key) {
  Node *node = findNode(root, key);

  if (node == nullptr) {
    return nullptr;
  }

  return &node->value;
}

template <typename Key, typename Value>
const Value *BinarySearchTree<Key, Value>::find(const Key &key) const {
  Node *node = findNode(root, key);

  if (node == nullptr) {
    return nullptr;
  }

  return &node->value;
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::keysInOrder(ArrayList<Key> &keys) const {
  keysInOrder(root, keys);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
  clear(root);
  root = nullptr;
  count = 0;
}

template <typename Key, typename Value>
int BinarySearchTree<Key, Value>::size() const {
  return count;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isEmpty() const {
  return count == 0;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node *
BinarySearchTree<Key, Value>::insertNode(Node *current, const Key &key,
                                         const Value &value,
                                         bool &addedNewNode) {
  if (current == nullptr) {
    addedNewNode = true;
    return new Node(key, value);
  }

  if (key < current->key) {
    current->left = insertNode(current->left, key, value, addedNewNode);
  } else if (key > current->key) {
    current->right = insertNode(current->right, key, value, addedNewNode);
  } else {
    current->value = value;
  }

  return current;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node *
BinarySearchTree<Key, Value>::findNode(Node *current, const Key &key) const {
  if (current == nullptr) {
    return nullptr;
  }

  if (key == current->key) {
    return current;
  }

  if (key < current->key) {
    return findNode(current->left, key);
  }

  return findNode(current->right, key);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::keysInOrder(Node *current,
                                               ArrayList<Key> &keys) const {
  if (current == nullptr) {
    return;
  }

  keysInOrder(current->left, keys);
  keys.pushBack(current->key);
  keysInOrder(current->right, keys);
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node *
BinarySearchTree<Key, Value>::copyTree(Node *current) {
  if (current == nullptr) {
    return nullptr;
  }

  Node *copy = new Node(current->key, current->value);
  copy->left = copyTree(current->left);
  copy->right = copyTree(current->right);
  return copy;
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(Node *current) {
  if (current == nullptr) {
    return;
  }

  clear(current->left);
  clear(current->right);
  delete current;
}
