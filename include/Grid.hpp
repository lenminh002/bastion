#pragma once

#include "Enemy.hpp"
#include "Tower.hpp"

class Grid {
  int rows;
  int cols;

public:
  Grid(int rows, int cols);

  void render(const Enemy &enemy, const Tower &tower) const;
};