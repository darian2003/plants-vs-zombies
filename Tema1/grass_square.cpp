#include <iostream>
#include "lab_m1/Tema1/grass_square.h"

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace m1;

bool GrassSquare::isEmpty() {
    if (empty)
        return true;
    return false;
}

GrassSquare::GrassSquare(bool empty, float cx, float cy, int row, int column) {
    this->empty = empty;
    this->cx = cx;
    this->cy = cy;
    this->row = row;
    this->column = column;
}

void GrassSquare::set(bool empty, float cx, float cy, int row, int column){
    this->empty = empty;
    this->cx = cx;
    this->cy = cy;
    this->row = row;
    this->column = column;
}

void GrassSquare::set(bool empty, float cx, float cy, int row, int column, float squareSide){
    this->empty = empty;
    this->cx = cx;
    this->cy = cy;
    this->row = row;
    this->column = column;
    this->squareSide = squareSide;
}


float GrassSquare::getCx() {
    return cx;
}

float GrassSquare::getCy() {
    return cy;
}

float GrassSquare::getSquareSide() {
    return squareSide;
}

void GrassSquare::setFighter() {
    this->empty = false;
}

void GrassSquare::unsetFighter() {
    this->empty = true;
}
