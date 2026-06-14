#pragma once

#include "ArrayList.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"

class Grid {
  int rows;
  int cols;

public:
  Grid(int rows, int cols);

  void render(const ArrayList<Enemy> &enemies,
              const ArrayList<Tower> &towers) const;
};