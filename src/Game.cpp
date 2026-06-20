#include "game/Game.hpp"
#include "core/Constants.hpp"
#include "game/MapValidator.hpp"
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

void printTowerType(HashTable<TowerType> &towerTypes, const string &name) {
  TowerType *towerType = towerTypes.find(name);
  if (towerType == nullptr) {
    return;
  }

  cout << towerType->name << ": damage " << towerType->damage << ", range "
       << towerType->range << ", cost " << towerType->cost << "\n";
}
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

  towerTypes.insert("cannon", TowerType{"cannon", 2, 3, 50});
  towerTypes.insert("sniper", TowerType{"sniper", 5, 6, 120});
  towerTypes.insert("rapid", TowerType{"rapid", 1, 2, 40});
}

void Game::run() {
  if (!validateMap()) {
    return;
  }

  printStartupInfo();

  int tick = 0;

  while (running) {
    clearScreen();

    spawnEnemies(tick);
    undoTowerPlacement(tick);
    fireProjectiles(tick);

    renderFrame();

    updateProjectiles();
    removeInactiveProjectiles();
    updateEnemies();
    updateTowers();
    checkGameOver();

    tick++;

    this_thread::sleep_for(chrono::milliseconds(300));
  }
}

bool Game::validateMap() const {
  MapValidator validator;
  if (!validator.hasPath(gameMap, spawnPosition, exitPosition)) {
    cout << "Invalid map: no path from spawn to exit\n";
    return false;
  }

  return true;
}

void Game::printStartupInfo() {
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

  cout << "Tower types:\n";
  printTowerType(towerTypes, "cannon");
  printTowerType(towerTypes, "sniper");
  printTowerType(towerTypes, "rapid");
  this_thread::sleep_for(chrono::milliseconds(1000));
}

void Game::clearScreen() const {
  // mac clear one time still show previous output on the terminal
  system("clear");
  system("clear");
}

void Game::spawnEnemies(int tick) {
  if (tick % 3 == 0 && !enemySpawnQueue.isEmpty()) {
    enemies.pushBack(enemySpawnQueue.dequeue());
    eventHistory.pushBack("Spawned enemy");
  }
}

void Game::undoTowerPlacement(int tick) {
  if (tick != 5 || towerUndoStack.isEmpty()) {
    return;
  }

  Position lastPosition = towerUndoStack.pop();
  for (int i = 0; i < towers.size(); i++) {
    if (towers[i].position().row == lastPosition.row &&
        towers[i].position().col == lastPosition.col) {
      towers.removeAt(i);
      eventHistory.pushBack("Undid tower placement");
      break;
    }
  }
}

void Game::fireProjectiles(int tick) {
  if (tick % 2 == 0) {
    projectiles.pushBack(Projectile(Position{3, 5}, 1));
    eventHistory.pushBack("Fired projectile");
  }
}

void Game::renderFrame() const {
  grid.render(enemies, towers, projectiles, gameMap);

  if (!eventHistory.isEmpty()) {
    cout << "Last event: " << eventHistory.back() << endl;
  }
}

void Game::updateProjectiles() {
  for (int i = 0; i < projectiles.size(); i++) {
    projectiles[i].update();
  }
}

void Game::removeInactiveProjectiles() {
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
}

void Game::updateEnemies() {
  for (int i = 0; i < enemies.size(); i++) {
    enemies[i].update();
  }
}

void Game::updateTowers() {
  for (int i = 0; i < towers.size(); i++) {
    towers[i].update();
  }
}

void Game::checkGameOver() {
  for (int i = 0; i < enemies.size(); i++) {
    if (enemySpawnQueue.isEmpty() && enemies[i].reachedExit()) {
      eventHistory.pushBack("Game Over");
      running = false;
    }
  }
}
