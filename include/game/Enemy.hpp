#pragma once

#include "core/Position.hpp"

class Enemy {
  Position pos;

public:
  Enemy();
  Enemy(Position start);

  void update();
  Position position() const;
  bool reachedExit() const;
};
