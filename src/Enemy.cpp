#include "Enemy.hpp"

Enemy::Enemy(Position start) : pos(start) {}

void Enemy::update() { pos.col += 1; }

Position Enemy::position() const { return pos; }

bool Enemy::reachedExit() const { return pos.col >= 9; }