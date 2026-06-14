#include "Grid.hpp"
#include <iostream>
using namespace std;

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {}

void Grid::render(const ArrayList<Enemy> &enemies,
                  const ArrayList<Tower> &towers) const {

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {

      // check if there is an enemy at the current position
      bool enemyHere = false;
      for (int e = 0; e < enemies.size(); e++) {
        Position enemyPos = enemies[e].position();

        if (enemyPos.row == row && enemyPos.col == col) {
          enemyHere = true;
        }
      }

      // check if there is a tower at the current position
      bool towerHere = false;
      for (int t = 0; t < towers.size(); t++) {
        Position towerPos = towers[t].position();

        if (towerPos.row == row && towerPos.col == col) {
          towerHere = true;
        }
      }

      if (enemyHere) {
        cout << "E";
      } else if (towerHere) {
        cout << "T";
      } else {
        cout << ".";
      }
    }
    cout << "\n";
  }
}