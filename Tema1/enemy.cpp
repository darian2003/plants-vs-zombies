#include <iostream>
#include "lab_m1/Tema1/enemy.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

Enemy::Enemy(std::string color, int level, float leftBorder, float bottomBorder) {
    this->color = color;
    this->hp = 3;
    this->level = level;
    this->leftBorder = leftBorder; 
    this->bottomBorder = bottomBorder;
    this->scale = 1;
}

void Enemy::setX(float x) {
    leftBorder = x;
}

void Enemy::setY(float y) {
    bottomBorder = y;
}

float Enemy::getX() {
    return leftBorder;
}

float Enemy::getY() {
    return bottomBorder;
}

std::string Enemy::getColor() {
    return color;
}

int Enemy::getHp() {
    return hp;
}

int Enemy::scaleDown(float deltaTime) {
    scale -= deltaTime;
    if (scale <= 0) {
        scale = 0;
        return 1;
    }
    return 0;
}

void Enemy::setScale(float scale) {
    this->scale = scale;
}

float Enemy::getScale() {
    return scale;
}

int Enemy::updateHp() {
    hp--;
    if (hp <= 0) {
        return 1;
    }
    return 0;
}

void Enemy::setColor(std::string color) {
    this->color = color;
}