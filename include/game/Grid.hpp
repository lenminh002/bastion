#pragma once

#include "core/Constants.hpp"
#include "game/Enemy.hpp"
#include "game/Projectile.hpp"
#include "game/Tower.hpp"
#include "structures/ArrayList.hpp"
#include "structures/SinglyLinkedList.hpp"

class Grid {
  int rows;
  int cols;

public:
  Grid(int rows, int cols);

  void render(const ArrayList<Enemy> &enemies, const ArrayList<Tower> &towers,
              const SinglyLinkedList<Projectile> &projectiles,
              const char map[Constants::gridRows][Constants::gridCols]) const;
};
