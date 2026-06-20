#include "structures/BinarySearchTree.hpp"
#include "structures/ArrayList.hpp"

#include <iostream>
#include <string>

namespace {
constexpr const char *green = "\033[32m";
constexpr const char *red = "\033[31m";
constexpr const char *reset = "\033[0m";
}

bool expect(bool condition, const char *message) {
  if (!condition) {
    std::cout << red << "FAIL" << reset << ": " << message << "\n";
    return false;
  }

  std::cout << green << "PASS" << reset << ": " << message << "\n";
  return true;
}

int main() {
  bool passed = true;

  BinarySearchTree<int, std::string> tree;

  passed = expect(tree.isEmpty(), "new tree starts empty") && passed;
  passed = expect(tree.size() == 0, "new tree starts with size 0") && passed;
  passed = expect(!tree.contains(10), "empty tree does not contain key") &&
           passed;
  passed = expect(tree.find(10) == nullptr, "find missing key returns nullptr") &&
           passed;

  tree.insert(2, "Damage");
  tree.insert(1, "Range");
  tree.insert(3, "Fire Rate");

  passed = expect(!tree.isEmpty(), "insert makes tree non-empty") && passed;
  passed = expect(tree.size() == 3, "insert increases size for new keys") &&
           passed;
  passed = expect(tree.contains(1), "contains finds left child") && passed;
  passed = expect(tree.contains(2), "contains finds root") && passed;
  passed = expect(tree.contains(3), "contains finds right child") && passed;
  passed = expect(!tree.contains(99), "contains rejects missing key") && passed;

  std::string *levelOne = tree.find(1);
  std::string *levelTwo = tree.find(2);
  std::string *levelThree = tree.find(3);

  passed = expect(levelOne != nullptr && *levelOne == "Range",
                  "find returns value for smaller key") &&
           passed;
  passed = expect(levelTwo != nullptr && *levelTwo == "Damage",
                  "find returns value for root key") &&
           passed;
  passed = expect(levelThree != nullptr && *levelThree == "Fire Rate",
                  "find returns value for larger key") &&
           passed;

  tree.insert(2, "Armor Pierce");
  passed = expect(tree.size() == 3,
                  "inserting duplicate key updates without increasing size") &&
           passed;
  passed = expect(tree.find(2) != nullptr && *tree.find(2) == "Armor Pierce",
                  "duplicate key updates existing value") &&
           passed;

  BinarySearchTree<int, std::string> copy = tree;
  copy.insert(4, "Splash");
  copy.insert(1, "Long Range");

  passed = expect(tree.size() == 3,
                  "copy constructor keeps original size independent") &&
           passed;
  passed = expect(copy.size() == 4, "copy can add its own node") && passed;
  passed = expect(tree.find(1) != nullptr && *tree.find(1) == "Range",
                  "copy update does not modify original value") &&
           passed;
  passed = expect(copy.find(1) != nullptr && *copy.find(1) == "Long Range",
                  "copy stores its own updated value") &&
           passed;

  BinarySearchTree<int, std::string> assigned;
  assigned.insert(100, "Temporary");
  assigned = tree;
  assigned.insert(5, "Critical");
  assigned.insert(3, "Rapid Fire");

  passed = expect(tree.size() == 3,
                  "copy assignment keeps original size independent") &&
           passed;
  passed = expect(assigned.size() == 4, "assigned tree can add its own node") &&
           passed;
  passed = expect(tree.find(3) != nullptr && *tree.find(3) == "Fire Rate",
                  "assigned update does not modify original value") &&
           passed;
  passed = expect(assigned.find(3) != nullptr &&
                      *assigned.find(3) == "Rapid Fire",
                  "assigned tree stores its own updated value") &&
           passed;

  assigned.clear();
  passed = expect(assigned.isEmpty(), "clear makes tree empty") && passed;
  passed = expect(assigned.size() == 0, "clear resets size") && passed;
  passed = expect(assigned.find(2) == nullptr,
                  "find after clear returns nullptr") &&
           passed;

  const BinarySearchTree<int, std::string> constTree = tree;
  const std::string *constFind = constTree.find(2);
  passed = expect(constFind != nullptr && *constFind == "Armor Pierce",
                  "const find returns const value pointer") &&
           passed;

  BinarySearchTree<int, std::string> traversalTree;
  traversalTree.insert(5, "Five");
  traversalTree.insert(2, "Two");
  traversalTree.insert(8, "Eight");
  traversalTree.insert(1, "One");
  traversalTree.insert(3, "Three");

  ArrayList<int> keys;
  traversalTree.keysInOrder(keys);

  passed = expect(keys.size() == 5, "keysInOrder writes every key") && passed;
  passed = expect(keys[0] == 1, "keysInOrder returns smallest key first") &&
           passed;
  passed = expect(keys[1] == 2, "keysInOrder returns second key in order") &&
           passed;
  passed = expect(keys[2] == 3, "keysInOrder returns middle key in order") &&
           passed;
  passed = expect(keys[3] == 5, "keysInOrder returns root key in order") &&
           passed;
  passed = expect(keys[4] == 8, "keysInOrder returns largest key last") &&
           passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All BinarySearchTree tests passed\n";
  return 0;
}
