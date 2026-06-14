#include "Queue.hpp"

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

  Queue<int> queue;

  passed = expect(queue.size() == 0, "new queue starts with size 0") && passed;
  passed = expect(queue.isEmpty(), "new queue starts empty") && passed;

  queue.enqueue(10);
  passed = expect(queue.size() == 1, "enqueue increases size to 1") && passed;
  passed =
      expect(!queue.isEmpty(), "queue is not empty after enqueue") && passed;
  passed =
      expect(queue.peek() == 10, "peek returns first enqueued value") && passed;

  queue.enqueue(20);
  queue.enqueue(30);

  passed = expect(queue.size() == 3, "multiple enqueues update size") && passed;
  passed =
      expect(queue.dequeue() == 10, "dequeue returns first value") && passed;
  passed =
      expect(queue.dequeue() == 20, "dequeue preserves FIFO order") && passed;
  passed = expect(queue.size() == 1, "dequeue decreases size") && passed;
  passed =
      expect(queue.peek() == 30, "peek returns next front value") && passed;

  queue.enqueue(40);
  queue.enqueue(50);
  queue.enqueue(60);

  passed =
      expect(queue.size() == 4, "wraparound fills available slots") && passed;
  passed = expect(queue[0] == 30, "logical index 0 is current front") && passed;
  passed = expect(queue[1] == 40, "logical index 1 follows front") && passed;
  passed = expect(queue[2] == 50, "logical index 2 follows front") && passed;
  passed = expect(queue[3] == 60, "logical index 3 follows front") && passed;

  queue.enqueue(70);
  passed = expect(queue.size() == 5, "enqueue past capacity resizes queue") &&
           passed;
  passed =
      expect(queue.dequeue() == 30, "resize preserves first logical value") &&
      passed;
  passed =
      expect(queue.dequeue() == 40, "resize preserves second logical value") &&
      passed;
  passed =
      expect(queue.dequeue() == 50, "resize preserves third logical value") &&
      passed;
  passed =
      expect(queue.dequeue() == 60, "resize preserves fourth logical value") &&
      passed;
  passed =
      expect(queue.dequeue() == 70, "resize preserves newest value") && passed;
  passed =
      expect(queue.isEmpty(), "queue is empty after removing all values") &&
      passed;

  Queue<int> original;
  original.enqueue(1);
  original.enqueue(2);
  original.enqueue(3);

  Queue<int> copy = original;
  copy.dequeue();
  copy.enqueue(99);

  passed = expect(original.peek() == 1,
                  "copy constructor keeps original front independent") &&
           passed;
  passed =
      expect(copy.peek() == 2, "copy can dequeue without changing original") &&
      passed;

  Queue<int> assigned;
  assigned.enqueue(100);
  assigned = original;
  assigned.dequeue();
  assigned.enqueue(77);

  passed = expect(original.peek() == 1,
                  "copy assignment keeps original front independent") &&
           passed;
  passed = expect(assigned.peek() == 2,
                  "assigned queue can dequeue without changing original") &&
           passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All Queue tests passed\n";
  return 0;
}