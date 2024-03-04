#pragma once

#include "components/simple_scene.h"
#include <vector>

namespace m1 {
    class Enemy {
        public:
            Enemy(){}
            ~Enemy(){
            }
            Enemy(std::string color, int level, float leftBorder, float bottomBorder);
            std::string getColor();
            float getX();
            float getY();
            void setX(float x);
            void setY(float y);
            int scaleDown(float deltaTime); // returns 1 if enemy completely disappeared
            float getScale();
            int getHp();
            int updateHp(); // returns 1 if hp becomes 0
            void setScale(float scale);
            void setColor(std::string color);
        protected:
            std::string color;
            int hp;
            int level; // from 0 to 2
            float leftBorder;
            float bottomBorder;
            float scale = 1;
    };


}