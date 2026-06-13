#pragma once

#include "Enemy.hpp"
#include "Grid.hpp"
#include "Tower.hpp"

class Game {
  Grid grid;
  Enemy enemy;
  Tower tower;
  bool running;

public:
  Game();

  void run();
};