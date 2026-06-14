#include "Tower.hpp"

Tower::Tower()
    : pos(Position{-1, -1}), range(0), damage(0), fireRate(0), cooldown(0) {}

Tower::Tower(Position start)
    : pos(start), range(2), damage(1), fireRate(1), cooldown(0) {}

void Tower::update() {}

Position Tower::position() const { return pos; }