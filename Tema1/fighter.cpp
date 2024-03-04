#include <iostream>
#include "lab_m1/Tema1/fighter.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

void Fighter::setFighter (std::string color, float x, float y) {
    this->color = color;
    this->x = x;
    this->y = y;
    this->timeUntilNextShot = 100;
}

Fighter::Fighter (std::string color, float x, float y) {
    this->color = color;
    this->x = x;
    this->y = y;
    this->timeUntilNextShot = 100;
    this->timeLeft = 100;
    this->scale = 1;
    this->isSet = false;
}

float Fighter::getX() {
    return x;
}

float Fighter::getY() {
    return y;
}

std::string Fighter::getColor() {
    return color;
}

void Fighter::setX(int x)  {
    this->x = x;
}    

void Fighter::setY(int y)  {
    this->y = y;
}  

float Fighter::getTimeLeft() {
    return timeLeft;
}

float Fighter::getTimeUntilNextShot() {
    return timeUntilNextShot;
}

void Fighter::setTimeLeft(float timeLeft) {
    this->timeLeft = timeLeft;
}

int Fighter::tryToShoot(float deltaTime) {
    timeLeft -= deltaTime * 100;
    if (timeLeft < 0) {
        timeLeft = timeUntilNextShot;
        return 1;
    }
    return 0;
}

int Fighter::scaleDown(float deltaTime) {
    scale -= 1 * deltaTime;
    if (scale <= 0) {
        scale = 0;
        return 1;
    }
    return 0;
}

float Fighter::getScale() {
    return scale;
}

bool Fighter::checkIfSet() {
    return isSet;
}

void Fighter::setFighter() {
    isSet = true;
}
void Fighter::unsetFighter() {
    isSet = false;
}

void Fighter::setScale(float scale) {
    this->scale = scale;
}