#include "Tower.hpp"

Tower::Tower(Position start)
    : pos(start), range(2), damage(1), fireRate(1), cooldown(0) {}

void Tower::update() {}

Position Tower::position() const { return pos; }