#include "Game.hpp"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

Game::Game() : grid(5, 10), running(true) {
  enemies.pushBack(Enemy(Position{1, 0}));
  enemies.pushBack(Enemy(Position{2, 0}));
  towers.pushBack(Tower(Position{3, 2}));
  towers.pushBack(Tower(Position{3, 4}));
}

void Game::run() {
  while (running) {
    // mac clear one time still show previous output on the terminal
    system("clear");
    system("clear");

    grid.render(enemies, towers);

    for (int i = 0; i < enemies.size(); i++) {
      enemies[i].update();
    }
    for (int i = 0; i < towers.size(); i++) {
      towers[i].update();
    }

    for (int i = 0; i < enemies.size(); i++) {
      if (enemies[i].reachedExit()) {
        running = false;
      }
    }

    this_thread::sleep_for(chrono::milliseconds(300));
  }
}
