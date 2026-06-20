#include "structures/DoublyLinkedList.hpp"

#include <iostream>

namespace {
constexpr const char *green = "\033[32m";
constexpr const char *red = "\033[31m";
constexpr const char *reset = "\033[0m";
} // namespace

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

  DoublyLinkedList<int> list;

  passed = expect(list.isEmpty(), "new list starts empty") && passed;
  passed = expect(list.size() == 0, "new list starts with size 0") && passed;

  list.pushFront(20);
  list.pushFront(10);

  passed = expect(list.size() == 2, "pushFront increases size") && passed;
  passed = expect(list.front() == 10, "front returns head value") && passed;
  passed = expect(list.back() == 20, "back returns tail value") && passed;
  passed = expect(list[0] == 10, "operator[] reads head") && passed;
  passed = expect(list[1] == 20, "operator[] reads tail") && passed;

  list.pushBack(30);
  list.pushBack(40);

  passed = expect(list.size() == 4, "pushBack increases size") && passed;
  passed = expect(list.back() == 40, "pushBack updates tail") && passed;
  passed = expect(list[2] == 30, "pushBack appends first new value") && passed;
  passed = expect(list[3] == 40, "pushBack appends second new value") && passed;

  list[1] = 99;
  passed =
      expect(list[1] == 99, "operator[] allows modifying values") && passed;

  list.removeAt(1);
  passed =
      expect(list.size() == 3, "removeAt from middle decreases size") && passed;
  passed =
      expect(list[0] == 10, "removeAt from middle preserves head") && passed;
  passed = expect(list[1] == 30, "removeAt from middle links next pointer") &&
           passed;
  passed =
      expect(list[2] == 40, "removeAt from middle preserves tail") && passed;
  passed =
      expect(list.back() == 40, "tail remains correct after middle remove") &&
      passed;

  list.removeAt(0);
  passed =
      expect(list.size() == 2, "removeAt from front decreases size") && passed;
  passed =
      expect(list.front() == 30, "removeAt from front updates head") && passed;
  passed =
      expect(list.back() == 40, "removeAt from front preserves tail") && passed;

  list.removeAt(list.size() - 1);
  passed =
      expect(list.size() == 1, "removeAt from back decreases size") && passed;
  passed =
      expect(list.front() == 30, "single remaining value is front") && passed;
  passed = expect(list.back() == 30, "single remaining value is also back") &&
           passed;

  list.removeAt(-1);
  passed = expect(list.size() == 1,
                  "removeAt with negative index leaves size unchanged") &&
           passed;

  list.removeAt(99);
  passed = expect(list.size() == 1,
                  "removeAt with too-large index leaves size unchanged") &&
           passed;

  DoublyLinkedList<int> original;
  original.pushBack(1);
  original.pushBack(2);
  original.pushBack(3);

  DoublyLinkedList<int> copy = original;
  copy[0] = 99;

  passed =
      expect(original[0] == 1, "copy constructor creates independent nodes") &&
      passed;
  passed = expect(copy[0] == 99, "copy can modify its own head") && passed;
  passed = expect(copy.back() == 3, "copy preserves tail value") && passed;

  DoublyLinkedList<int> assigned;
  assigned.pushBack(100);
  assigned = original;
  assigned[1] = 77;

  passed = expect(original[1] == 2,
                  "copy assignment keeps original nodes independent") &&
           passed;
  passed = expect(assigned[1] == 77, "assigned list can modify its own node") &&
           passed;
  passed =
      expect(assigned.front() == 1, "assigned list preserves front") && passed;
  passed =
      expect(assigned.back() == 3, "assigned list preserves back") && passed;

  list.clear();
  passed = expect(list.isEmpty(), "clear makes list empty") && passed;
  passed = expect(list.size() == 0, "clear resets size") && passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All DoublyLinkedList tests passed\n";
  return 0;
}
