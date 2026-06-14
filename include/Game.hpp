#pragma once

#include "ArrayList.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Tower.hpp"

class Game {
  Grid grid;
  ArrayList<Enemy> enemies;
  ArrayList<Tower> towers;
  bool running;

public:
  Game();

  void run();
};