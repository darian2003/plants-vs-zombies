#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace m1 {

    class VisualElement {
        public:
            VisualElement(){}
            ~VisualElement(){}
        public:
            VisualElement(std::string name, float leftBorder, float bottomBorder, glm::vec3 color) { // Constructor with parameters
                this->name = name;
                this->leftBorder = leftBorder;
                this->bottomBorder = bottomBorder;
                this->color = color;
            }

        public:
            float leftBorder;
            float bottomBorder;
            glm::vec3 color;
            std::string name;
    };

}