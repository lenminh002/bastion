#pragma once

#include "ArrayList.hpp"
#include "Constants.hpp"
#include "Enemy.hpp"
#include "Projectile.hpp"
#include "SinglyLinkedList.hpp"
#include "Tower.hpp"

class Grid {
  int rows;
  int cols;

public:
  Grid(int rows, int cols);

  void render(const ArrayList<Enemy> &enemies, const ArrayList<Tower> &towers,
              const SinglyLinkedList<Projectile> &projectiles,
              const char map[Constants::gridRows][Constants::gridCols]) const;
};