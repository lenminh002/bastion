#include "MapValidator.hpp"

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
  MapValidator validator;

  const char straightPath[gridRows][gridCols] = {
      {'S', '.', '.', '.', '.', '.', '.', '.', '.', 'E'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
  };

  passed = expect(validator.hasPath(straightPath, Position{0, 0},
                                    Position{0, 9}),
                  "straight path succeeds") &&
           passed;

  const char blockedPath[gridRows][gridCols] = {
      {'S', '#', '#', '#', '#', '#', '#', '#', '#', 'E'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
  };

  passed = expect(!validator.hasPath(blockedPath, Position{0, 0},
                                     Position{0, 9}),
                  "blocked path fails") &&
           passed;

  const char pathAroundObstacle[gridRows][gridCols] = {
      {'S', '.', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '.', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '.', '.', '.', '.', '.', '.', '.', '.', 'E'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
  };

  passed = expect(validator.hasPath(pathAroundObstacle, Position{0, 0},
                                    Position{2, 9}),
                  "path around obstacle succeeds") &&
           passed;

  const char startEqualsExit[gridRows][gridCols] = {
      {'S', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
      {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
  };

  passed = expect(validator.hasPath(startEqualsExit, Position{0, 0},
                                    Position{0, 0}),
                  "start equals exit succeeds") &&
           passed;

  const char openLoop[gridRows][gridCols] = {
      {'S', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
      {'.', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
      {'.', '#', '.', '.', '.', '.', '.', '#', '.', '#'},
      {'.', '#', '.', '#', '#', '#', '.', '#', '.', '#'},
      {'.', '.', '.', '#', '#', '#', '.', '.', '.', 'E'},
  };

  passed = expect(validator.hasPath(openLoop, Position{0, 0}, Position{4, 9}),
                  "visited cells prevent infinite loops") &&
           passed;

  const char outOfBoundsStart[gridRows][gridCols] = {
      {'S', '.', '.', '.', '.', '.', '.', '.', '.', 'E'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
      {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
  };

  passed = expect(!validator.hasPath(outOfBoundsStart, Position{-1, 0},
                                     Position{0, 9}),
                  "out-of-bounds start fails") &&
           passed;

  if (!passed) {
    return 1;
  }

  std::cout << "All MapValidator tests passed\n";
  return 0;
}
