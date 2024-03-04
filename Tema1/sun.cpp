#include <iostream>
#include "lab_m1/Tema1/sun.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

Sun::Sun(float targetX, float targetY) {
    this->x = targetX;
    this->y = 760;
    this->targetY = targetY;
    this->isCollected = false;
}

void Sun::setY(float y) {
    this->y = y;
}

bool Sun::checkIfReachedTarget() {
    if (y <= targetY)
        return true;
    return false;
}

float Sun::getY() {
    return y;
}

float Sun::getX() {
    return x;
}

float Sun::getTargetY() {
    return targetY;
}

int Sun::sunFallEffect(float deltaTime) {
    if (y <= targetY) {
        y = targetY;
        return 1;
    }
    y -= 100 * deltaTime;
    return 0;
}

void Sun::removeSun(){
    this->isCollected = true;
}

bool Sun::getCollected() {
    return isCollected;
}