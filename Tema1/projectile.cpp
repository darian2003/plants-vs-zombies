#include <iostream>
#include "lab_m1/Tema1/projectile.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

Projectile::Projectile(float x, float y, std::string color) {
    this->x = x;
    this->y = y;
    this->color = color;
    this->xDegree = 0;
}

void Projectile::setX(float x) {
    this->x = x;
}
float Projectile::getX() {
    return x;
}

float Projectile::getY() {
    return y;
}

float Projectile::getXDegree() {
    return xDegree;
}

void Projectile::updateXDegree(float deltaTime) {
    this->xDegree -= deltaTime * 10;
}

void Projectile::updateX(float deltaTime) {
    this->x += deltaTime * 200;
}

std::string Projectile::getColor() {
    return color;
}

