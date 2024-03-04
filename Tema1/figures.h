#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace figures {
    float toRadians(float xDegrees);
    Mesh *CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh *CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
    Mesh *CreateRhombus(const std::string &name, glm::vec3 leftBottomCorner, float side, float angle, glm::vec3 color, bool fill);
    // change pentagonSide to starCircumradius if time 
    Mesh *CreateStar(const std::string &name, glm::vec3 centerOfGravity, float starCircumradius, glm::vec3 color, bool fill);
    Mesh *CreateEnemy(const std::string &name, glm::vec3 centerOfGravity, float hexagonRadius, glm::vec3 outerColor, glm::vec3 innerColor, bool fill);
    Mesh *CreateHeart(const std::string &name, glm::vec3 centerOfGravity, float heartHeight, glm::vec3 color, bool fill);
    Mesh *CreateSun(const std::string &name, glm::vec3 centerOfGravity, float sunRadius, float octagonRadius, glm::vec3 interiorColor, glm::vec3 outerColor, bool fill);
}