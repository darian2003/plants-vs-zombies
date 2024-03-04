#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class BlackBox {
        public:
            BlackBox(){}
            ~BlackBox(){}
            BlackBox(float offsetX, float offsetY, float squareSide, std::string fighterColor, int price);
            float getX();
            float getY();
            float getSize();
            std::string getColor();
            int getPrice();
        protected:
        float offsetX, offsetY;
        float squareSide;
        std::string fighterColor;
        int price;
    };
}