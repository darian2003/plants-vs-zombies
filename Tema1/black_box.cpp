#include <iostream>
#include "lab_m1/Tema1/black_box.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

BlackBox::BlackBox(float offsetX, float offsetY, float squareSide, std::string fighterColor, int price) {
    this->offsetX = offsetX;
    this->offsetY = offsetY;
    this->fighterColor = fighterColor;
    this->squareSide = squareSide;
    this->price = price;
}

float BlackBox::getX() {
    return offsetX;
}

float BlackBox::getY() {
    return offsetY;
}

float BlackBox::getSize() {
    return squareSide;
}

std::string BlackBox::getColor() {
    return fighterColor;
}

int BlackBox::getPrice() {
    return price;
}

