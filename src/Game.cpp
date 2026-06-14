#include "Game.hpp"
#include <chrono>
#include <thread>
using namespace std;

Game::Game() : grid(5, 10), running(true) {
  enemySpawnQueue.enqueue(Enemy(Position{1, 0}));
  enemySpawnQueue.enqueue(Enemy(Position{1, 0}));

  towers.pushBack(Tower(Position{3, 2}));
  towerUndoStack.push(Position{3, 2});
  towers.pushBack(Tower(Position{3, 4}));
  towerUndoStack.push(Position{3, 4});
}

void Game::run() {
  int tick = 0;

  while (running) {
    // mac clear one time still show previous output on the terminal
    system("clear");
    system("clear");

    if (tick % 3 == 0 && !enemySpawnQueue.isEmpty()) {
      enemies.pushBack(enemySpawnQueue.dequeue());
    }

    if (tick == 5 && !towerUndoStack.isEmpty()) {
      Position lastPosition = towerUndoStack.pop();
      // find index of tower with same position
      for (int i = 0; i < towers.size(); i++) {
        if (towers[i].position().row == lastPosition.row &&
            towers[i].position().col == lastPosition.col) {
          towers.removeAt(i);
          break;
        }
      }
    }

    grid.render(enemies, towers);

    for (int i = 0; i < enemies.size(); i++) {
      enemies[i].update();
    }
    for (int i = 0; i < towers.size(); i++) {
      towers[i].update();
    }

    for (int i = 0; i < enemies.size(); i++) {
      if (enemySpawnQueue.isEmpty() && enemies[i].reachedExit()) {
        running = false;
      }
    }

    tick++;

    this_thread::sleep_for(chrono::milliseconds(300));
  }
}
