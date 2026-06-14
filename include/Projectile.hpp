#pragma once

#include "Position.hpp"

class Projectile {
  Position pos;
  int damage;
  bool active;

public:
  Projectile();
  Projectile(Position start, int damage);

  void update();
  Position position() const { return pos; }
  int getDamage() const { return damage; }
  bool isActive() const { return active; }
  void deactivate() { active = false; }
};

inline Projectile::Projectile()
    : pos(Position{-1, -1}), damage(0), active(false) {}

inline Projectile::Projectile(Position start, int damage)
    : pos(start), damage(damage), active(true) {}

inline void Projectile::update() {
  if (!active) {
    return;
  }

  pos.col += 1;

  if (pos.col > 9) {
    active = false;
  }
}
