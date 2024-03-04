#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class Projectile {
        public:
            Projectile(){}
            ~Projectile(){}
            Projectile(float x, float y, std::string color);
            void setX(float x);
            float getX();
            float getY();
            float getXDegree();
            std::string getColor();
            void updateXDegree(float deltaTime);
            void updateX(float deltaTime);

        protected:
            float x, y;
            std::string color;
            float xDegree; 
    };
}