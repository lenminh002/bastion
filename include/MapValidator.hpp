#pragma once

#include "Constants.hpp"
#include "Position.hpp"

const int gridRows = Constants::gridRows;
const int gridCols = Constants::gridCols;

class MapValidator {

public:
  bool hasPath(const char map[gridRows][gridCols], Position start,
               Position exit) const;

private:
  bool search(const char map[gridRows][gridCols],
              bool visited[gridRows][gridCols], Position current,
              Position exit) const;

  bool isOutOfBounds(Position position) const;
};

inline bool MapValidator::isOutOfBounds(Position position) const {
  return (position.row < 0 || position.row >= gridRows || position.col < 0 ||
          position.col >= gridCols);
}

inline bool MapValidator::hasPath(const char map[gridRows][gridCols],
                                  Position start, Position exit) const {

  bool visited[gridRows][gridCols];

  for (int i = 0; i < gridRows; i++) {
    for (int j = 0; j < gridCols; j++) {
      visited[i][j] = false;
    }
  }
  return search(map, visited, start, exit);
}

inline bool MapValidator::search(const char map[gridRows][gridCols],
                                 bool visited[gridRows][gridCols],
                                 Position current, Position exit) const {

  if (isOutOfBounds(current) || visited[current.row][current.col] ||
      map[current.row][current.col] == '#') {
    return false;
  }

  if (current.row == exit.row && current.col == exit.col) {
    return true;
  }

  visited[current.row][current.col] = true;

  Position up = {current.row - 1, current.col};
  Position down = {current.row + 1, current.col};
  Position left = {current.row, current.col - 1};
  Position right = {current.row, current.col + 1};

  return search(map, visited, up, exit) || search(map, visited, down, exit) ||
         search(map, visited, left, exit) || search(map, visited, right, exit);
}
