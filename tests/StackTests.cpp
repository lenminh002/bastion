#include "structures/Stack.hpp"

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

  Stack<int> stack;

  passed = expect(stack.isEmpty(), "new stack starts empty") && passed;
  passed = expect(stack.size() == 0, "new stack starts with size 0") && passed;
  passed =
      expect(stack.peek() == 0, "peek on empty stack returns default int") &&
      passed;
  passed = expect(stack.pop() == 0, "pop on empty stack returns default int") &&
           passed;
  passed = expect(stack.isEmpty(), "empty pop leaves stack empty") && passed;

  stack.push(10);
  passed = expect(!stack.isEmpty(), "push makes stack non-empty") && passed;
  passed = expect(stack.size() == 1, "push increases size to 1") && passed;
  passed =
      expect(stack.peek() == 10, "peek returns last pushed value") && passed;

  stack.push(20);
  stack.push(30);

  passed = expect(stack.size() == 3, "multiple pushes update size") && passed;
  passed =
      expect(stack.peek() == 30, "peek returns most recent value") && passed;
  passed = expect(stack.pop() == 30, "pop returns most recent value first") &&
           passed;
  passed = expect(stack.pop() == 20, "pop follows LIFO order") && passed;
  passed =
      expect(stack.peek() == 10, "peek sees remaining top value") && passed;
  passed = expect(stack.size() == 1, "pop decreases size") && passed;
  passed = expect(stack.pop() == 10, "pop returns oldest value last") && passed;
  passed = expect(stack.isEmpty(), "stack is empty after all pops") && passed;

  for (int i = 0; i < 25; i++) {
    stack.push(i);
  }

  passed = expect(stack.size() == 25, "stack grows through ArrayList resize") &&
           passed;
  passed = expect(stack.peek() == 24, "top survives after resize") && passed;
  passed = expect(stack.pop() == 24, "pop after resize returns newest value") &&
           passed;
  passed = expect(stack.pop() == 23, "LIFO order holds after resize") && passed;
  passed =
      expect(stack.size() == 23, "size updates after resize pops") && passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All Stack tests passed\n";
  return 0;
}
