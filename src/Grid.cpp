#include "Grid.hpp"
#include <iostream>
using namespace std;

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {}

void Grid::render(const Enemy &enemy, const Tower &tower) const {
  Position enemyPos = enemy.position();
  Position towerPos = tower.position();

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      if (row == enemyPos.row && col == enemyPos.col) {
        cout << "E";
      } else if (row == towerPos.row && col == towerPos.col) {
        cout << "T";
      } else {
        cout << ".";
      }
    }
    cout << "\n";
  }
}