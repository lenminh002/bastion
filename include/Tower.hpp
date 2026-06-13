#pragma once

#include "Position.hpp"

class Tower {
  Position pos;
  int range;
  int damage;
  int fireRate;
  int cooldown;

public:
  Tower(Position start);

  void update();
  Position position() const;
};