#include "structures/ArrayList.hpp"

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

  ArrayList<int> numbers;

  passed = expect(numbers.size() == 0, "new list starts with size 0") && passed;
  passed = expect(numbers.isEmpty(), "new list starts empty") && passed;

  numbers.pushBack(10);
  passed =
      expect(numbers.size() == 1, "pushBack increases size to 1") && passed;
  passed =
      expect(!numbers.isEmpty(), "list is not empty after pushBack") && passed;
  passed =
      expect(numbers[0] == 10, "first value is stored at index 0") && passed;

  numbers.pushBack(20);
  numbers.pushBack(30);

  passed = expect(numbers.size() == 3, "multiple pushBack calls update size") &&
           passed;
  passed =
      expect(numbers[1] == 20, "second value is stored at index 1") && passed;
  passed =
      expect(numbers[2] == 30, "third value is stored at index 2") && passed;

  numbers[1] = 99;
  passed =
      expect(numbers[1] == 99, "operator[] allows modifying values") && passed;

  for (int i = 0; i < 20; i++) {
    numbers.pushBack(i);
  }

  passed =
      expect(numbers.size() == 23, "size is correct after resize") && passed;
  passed = expect(numbers[0] == 10, "resize preserves old value at index 0") &&
           passed;
  passed =
      expect(numbers[1] == 99, "resize preserves modified value at index 1") &&
      passed;
  passed = expect(numbers[2] == 30, "resize preserves old value at index 2") &&
           passed;
  passed = expect(numbers[3] == 0,
                  "first value after resize test starts at index 3") &&
           passed;
  passed =
      expect(numbers[22] == 19, "last pushed value is present after resize") &&
      passed;

  ArrayList<int> original;
  original.pushBack(10);
  original.pushBack(20);

  ArrayList<int> copy = original;
  copy[0] = 99;

  passed = expect(original[0] == 10,
                  "copy constructor creates independent storage") &&
           passed;
  passed =
      expect(copy[0] == 99, "copy can modify its own first value") && passed;
  passed = expect(copy[1] == 20, "copy preserves second value") && passed;

  ArrayList<int> assigned;
  assigned.pushBack(100);
  assigned = original;
  assigned[0] = 77;

  passed = expect(original[0] == 10,
                  "copy assignment keeps original storage independent") &&
           passed;
  passed =
      expect(assigned[0] == 77, "assigned list can modify its own value") &&
      passed;
  passed = expect(assigned[1] == 20, "assigned list preserves copied values") &&
           passed;

  ArrayList<int> removable;
  removable.pushBack(10);
  removable.pushBack(20);
  removable.pushBack(30);
  removable.pushBack(40);

  removable.removeAt(1);
  passed =
      expect(removable.size() == 3, "removeAt from middle decreases size") &&
      passed;
  passed = expect(removable[0] == 10,
                  "removeAt from middle preserves value before index") &&
           passed;
  passed = expect(removable[1] == 30,
                  "removeAt from middle shifts next value left") &&
           passed;
  passed = expect(removable[2] == 40,
                  "removeAt from middle keeps later values in order") &&
           passed;

  removable.removeAt(0);
  passed =
      expect(removable.size() == 2, "removeAt from front decreases size") &&
      passed;
  passed =
      expect(removable[0] == 30, "removeAt from front shifts first value") &&
      passed;
  passed = expect(removable[1] == 40,
                  "removeAt from front preserves remaining order") &&
           passed;

  removable.removeAt(removable.size() - 1);
  passed = expect(removable.size() == 1, "removeAt from back decreases size") &&
           passed;
  passed = expect(removable[0] == 30,
                  "removeAt from back preserves earlier values") &&
           passed;

  removable.removeAt(-1);
  passed = expect(removable.size() == 1,
                  "removeAt with negative index leaves size unchanged") &&
           passed;
  passed = expect(removable[0] == 30,
                  "removeAt with negative index leaves values unchanged") &&
           passed;

  removable.removeAt(99);
  passed = expect(removable.size() == 1,
                  "removeAt with too-large index leaves size unchanged") &&
           passed;
  passed = expect(removable[0] == 30,
                  "removeAt with too-large index leaves values unchanged") &&
           passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All ArrayList tests passed\n";
  return 0;
}
