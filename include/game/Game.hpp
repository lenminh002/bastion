#pragma once

#include "core/Position.hpp"
#include "game/Enemy.hpp"
#include "game/Grid.hpp"
#include "game/Projectile.hpp"
#include "game/Tower.hpp"
#include "game/TowerUpgrade.hpp"
#include "structures/ArrayList.hpp"
#include "structures/BinarySearchTree.hpp"
#include "structures/DoublyLinkedList.hpp"
#include "structures/Queue.hpp"
#include "structures/SinglyLinkedList.hpp"
#include "structures/Stack.hpp"
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

  // BST for looking up tower upgrades by level
  BinarySearchTree<int, TowerUpgrade> towerUpgrades;

  bool running;

public:
  Game();

  void run();
};
