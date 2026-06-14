#include "SinglyLinkedList.hpp"

#include <iostream>

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

  SinglyLinkedList<int> list;

  passed = expect(list.isEmpty(), "new list starts empty") && passed;
  passed = expect(list.size() == 0, "new list starts with size 0") && passed;

  list.pushFront(20);
  list.pushFront(10);

  passed = expect(list.size() == 2, "pushFront increases size") && passed;
  passed = expect(list[0] == 10, "pushFront inserts at head") && passed;
  passed = expect(list[1] == 20, "old head shifts to next node") && passed;

  list.pushBack(30);
  list.pushBack(40);

  passed = expect(list.size() == 4, "pushBack increases size") && passed;
  passed = expect(list[2] == 30, "pushBack appends first new value") && passed;
  passed = expect(list[3] == 40, "pushBack appends second new value") && passed;

  list[1] = 99;
  passed = expect(list[1] == 99, "operator[] allows modifying values") &&
           passed;

  list.removeAt(1);
  passed =
      expect(list.size() == 3, "removeAt from middle decreases size") &&
      passed;
  passed = expect(list[0] == 10, "removeAt from middle preserves head") &&
           passed;
  passed = expect(list[1] == 30, "removeAt from middle links around target") &&
           passed;
  passed = expect(list[2] == 40, "removeAt from middle preserves tail") &&
           passed;

  list.removeAt(0);
  passed = expect(list.size() == 2, "removeAt from front decreases size") &&
           passed;
  passed = expect(list[0] == 30, "removeAt from front moves head") && passed;

  list.removeAt(list.size() - 1);
  passed = expect(list.size() == 1, "removeAt from back decreases size") &&
           passed;
  passed = expect(list[0] == 30, "removeAt from back preserves earlier value") &&
           passed;

  list.removeAt(-1);
  passed = expect(list.size() == 1,
                  "removeAt with negative index leaves size unchanged") &&
           passed;

  list.removeAt(99);
  passed = expect(list.size() == 1,
                  "removeAt with too-large index leaves size unchanged") &&
           passed;

  SinglyLinkedList<int> original;
  original.pushBack(1);
  original.pushBack(2);
  original.pushBack(3);

  SinglyLinkedList<int> copy = original;
  copy[0] = 99;

  passed = expect(original[0] == 1,
                  "copy constructor creates independent nodes") &&
           passed;
  passed = expect(copy[0] == 99, "copy can modify its own node") && passed;
  passed = expect(copy[2] == 3, "copy preserves later values") && passed;

  SinglyLinkedList<int> assigned;
  assigned.pushBack(100);
  assigned = original;
  assigned[1] = 77;

  passed = expect(original[1] == 2,
                  "copy assignment keeps original nodes independent") &&
           passed;
  passed = expect(assigned[1] == 77,
                  "assigned list can modify its own node") &&
           passed;
  passed = expect(assigned.size() == 3,
                  "assigned list receives copied size") &&
           passed;

  list.clear();
  passed = expect(list.isEmpty(), "clear makes list empty") && passed;
  passed = expect(list.size() == 0, "clear resets size") && passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All SinglyLinkedList tests passed\n";
  return 0;
}
