#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {
    class Fighter {
        public: 
            Fighter() {}
            ~Fighter(){}
            void setFighter(std::string color, float x, float y);
            Fighter (std::string color, float x, float y);
            float getX();
            float getY();
            std::string getColor();
            void setX(int x);
            void setY(int y);
            float getTimeLeft();
            float getTimeUntilNextShot();
            void setTimeLeft(float timeLeft);
            int tryToShoot(float deltaTime); // returns 1 if fighter can shoot
            int scaleDown(float deltaTime); // returns 1 if fighter completely disappeared
            float getScale();
            bool checkIfSet();
            void setFighter();
            void unsetFighter();
            void setScale(float scale);
        protected:
            std::string color;
            float x, y;
            float timeUntilNextShot, timeLeft;
            float scale = 1;
            bool isSet = false;
    };
}