#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class Sun {
        public:
            Sun(){}
            ~Sun(){}
            Sun(float targetY, float targetX);
            float getY();
            float getTargetY();
            float getX();
            void setY(float y);
            bool checkIfReachedTarget();
            int sunFallEffect(float deltaTime); // returns 1 if sun reached its target destination
            void removeSun();
            bool getCollected();

        protected:
            float x, y, targetY;
            bool isCollected;

    };
}