#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class GrassSquare {
        public:
            GrassSquare(){}
            ~GrassSquare(){}
            bool isEmpty();
            void set(bool empty, float cx, float cy, int row, int column);
            GrassSquare(bool empty, float cx, float cy, int row, int column);
            float getCx();
            float getCy();
            float getSquareSide();
            void set(bool empty, float cx, float cy, int row, int column, float squareSide);
            void setFighter();
            void unsetFighter();


        protected:
            float cx, cy; // center of the square
            bool empty = true;
            int row, column;
            float offsetX, offsetY; // left bottom corner coordinates
            float squareSide;

    };
}
