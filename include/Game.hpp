#pragma once

#include "ArrayList.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Queue.hpp"
#include "Tower.hpp"

class Game {
  Grid grid;
  ArrayList<Enemy> enemies;
  ArrayList<Tower> towers;
  Queue<Enemy> enemySpawnQueue;
  bool running;

public:
  Game();

  void run();
};