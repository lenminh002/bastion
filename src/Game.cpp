#include "Game.hpp"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

Game::Game()
    : grid(5, 10), enemy(Position{1, 0}), tower(Position{3, 4}), running(true) {
}

void Game::run() {
  while (running) {
    system("clear");

    grid.render(enemy, tower);

    enemy.update();
    tower.update();

    if (enemy.reachedExit()) {
      running = false;
    }

    this_thread::sleep_for(chrono::milliseconds(300));
  }
}
