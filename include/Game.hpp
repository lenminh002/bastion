#pragma once

#include "ArrayList.hpp"
#include "DoublyLinkedList.hpp"
#include "Enemy.hpp"
#include "Grid.hpp"
#include "Projectile.hpp"
#include "Queue.hpp"
#include "SinglyLinkedList.hpp"
#include "Stack.hpp"
#include "Tower.hpp"
#include <string>

class Game {
  Grid grid;
  ArrayList<Enemy> enemies;
  ArrayList<Tower> towers;
  SinglyLinkedList<Projectile> projectiles;
  DoublyLinkedList<std::string> eventHistory;

  // Queue for spawning enemies
  Queue<Enemy> enemySpawnQueue;

  // Stack for undoing tower placements
  Stack<Position> towerUndoStack;

  bool running;

public:
  Game();

  void run();
};