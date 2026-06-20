#include "Game.hpp"
#include "Constants.hpp"
#include "MapValidator.hpp"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

namespace {
const char gameMap[Constants::gridRows][Constants::gridCols] = {
    {'S', '.', '.', '.', '.', '#', '.', '.', '.', '.',
     '.', '.', '.', '.', '.', '.', '.', '.', '.', 'E'},
    {'#', '#', '#', '#', '.', '#', '.', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '.', '.', '.', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', 'T', '#', '#', '#', '.', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '#', '#', '#', '#', '#', '.', '.', '.', '.',
     '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
     '#', '#', '#', '#', '#', '#', '#', '#', '.', 'E'},
};
constexpr Position spawnPosition{0, 0};
constexpr Position exitPosition{0, Constants::lastGridCol};
} // namespace

Game::Game() : grid(Constants::gridRows, Constants::gridCols), running(true) {
  enemySpawnQueue.enqueue(Enemy(Position{1, 0}));
  enemySpawnQueue.enqueue(Enemy(Position{1, 0}));

  towers.pushBack(Tower(Position{3, 2}));
  towerUndoStack.push(Position{3, 2});
  eventHistory.pushBack("Built tower");

  towers.pushBack(Tower(Position{3, 4}));
  eventHistory.pushBack("Built tower");
  towerUndoStack.push(Position{3, 4});

  towerUpgrades.insert(1, TowerUpgrade{1, 1, 0, 50});
  towerUpgrades.insert(2, TowerUpgrade{2, 2, 1, 100});
  towerUpgrades.insert(3, TowerUpgrade{3, 4, 1, 200});
}

void Game::run() {
  MapValidator validator;
  if (!validator.hasPath(gameMap, spawnPosition, exitPosition)) {
    cout << "Invalid map: no path from spawn to exit\n";
    return;
  }

  ArrayList<int> upgradeLevels;
  towerUpgrades.keysInOrder(upgradeLevels);

  cout << "Tower upgrades:\n";
  for (int i = 0; i < upgradeLevels.size(); i++) {
    TowerUpgrade *upgrade = towerUpgrades.find(upgradeLevels[i]);
    if (upgrade != nullptr) {
      cout << "Level " << upgrade->level << ": +" << upgrade->damageBonus
           << " damage, +" << upgrade->rangeBonus << " range, cost "
           << upgrade->cost << "\n";
    }
  }
  this_thread::sleep_for(chrono::milliseconds(1000));

  int tick = 0;

  while (running) {
    // mac clear one time still show previous output on the terminal
    system("clear");
    system("clear");

    if (tick % 3 == 0 && !enemySpawnQueue.isEmpty()) {
      enemies.pushBack(enemySpawnQueue.dequeue());
      eventHistory.pushBack("Spawned enemy");
    }

    if (tick == 5 && !towerUndoStack.isEmpty()) {
      Position lastPosition = towerUndoStack.pop();
      // find index of tower with same position
      for (int i = 0; i < towers.size(); i++) {
        if (towers[i].position().row == lastPosition.row &&
            towers[i].position().col == lastPosition.col) {
          towers.removeAt(i);
          eventHistory.pushBack("Undid tower placement");
          break;
        }
      }
    }

    if (tick % 2 == 0) {
      projectiles.pushBack(Projectile(Position{3, 5}, 1));
      eventHistory.pushBack("Fired projectile");
    }

    grid.render(enemies, towers, projectiles, gameMap);

    // Print last event
    if (!eventHistory.isEmpty()) {
      cout << "Last event: " << eventHistory.back() << endl;
    }
    for (int i = 0; i < projectiles.size(); i++) {
      projectiles[i].update();
    }

    // removeAt(i) shifts the next projectile into index i, so only advance
    // when nothing was removed.
    int i = 0;
    while (i < projectiles.size()) {
      if (!projectiles[i].isActive()) {
        projectiles.removeAt(i);
      } else {
        i++;
      }
    }

    for (int i = 0; i < enemies.size(); i++) {
      enemies[i].update();
    }
    for (int i = 0; i < towers.size(); i++) {
      towers[i].update();
    }

    for (int i = 0; i < enemies.size(); i++) {
      if (enemySpawnQueue.isEmpty() && enemies[i].reachedExit()) {
        eventHistory.pushBack("Game Over");
        running = false;
      }
    }

    tick++;

    this_thread::sleep_for(chrono::milliseconds(300));
  }
}
