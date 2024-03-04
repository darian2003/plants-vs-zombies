#include <iostream>
#include "lab_m1/Tema1/figures.h"
#include <cmath>

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

float figures::toRadians(float xDegrees) {
    return xDegrees * 3.14159/180;
}

Mesh* figures::CreateSquare(
    const std::string &name,       
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

 Mesh *figures::CreateRectangle(const std::string &name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill) {
   
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

 Mesh *figures::CreateRhombus(const std::string &name, glm::vec3 leftBottomCorner, float side, float angle, glm::vec3 color, bool fill) {
   
    // converting degrees to radians
    float radians = figures::toRadians(angle);
    glm::vec3 corner = leftBottomCorner;
    // Distance to from the vertices to the center of gravity
    float cx = sin(radians/2) * side;
    float cy = cos(radians/2) * side;
    float rectangle_length = side * 0.95;
    float rectangle_height = 0.35 * side;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, -cy, 0), color),
        VertexFormat(corner + glm::vec3(cx, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, cy, 0), color),
        VertexFormat(corner + glm::vec3(-cx, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, rectangle_height/2, 0), color),
        VertexFormat(corner + glm::vec3(0, -rectangle_height/2, 0), color),
        VertexFormat(corner + glm::vec3(rectangle_length, -rectangle_height/2, 0), color),
        VertexFormat(corner + glm::vec3(rectangle_length, rectangle_height/2, 0), color)

    };

    Mesh* rhombus = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        0, 1, 2, 
        0, 2, 3,
        4, 5, 6,
        4, 6, 7
    };

    if (!fill) {
        rhombus->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rhombus->InitFromData(vertices, indices);
    return rhombus;
}

Mesh *figures::CreateStar(const std::string &name, glm::vec3 centerOfGravity, float starCircumradius, glm::vec3 color, bool fill) {

    // Step 1: Pentagon

    glm::vec3 center = centerOfGravity;
    float pentagonSide = 2 * starCircumradius / (tan(figures::toRadians(72)) + tan(figures::toRadians(54)));

    float pentagonAngle = 108;
    float phi = figures::toRadians(pentagonAngle / 2);
    float circumradius = pentagonSide / (2 * cos(phi));
    float inradius = circumradius * sin(phi); // this in pentagon's height

    // Step 2: Star
    float starAngle = 36;
    float theta = figures::toRadians(starAngle / 2);
    float starSide = pentagonSide / (2 * sin(theta));
    //float starCircumradius = inradius + starSide * cos(theta); // = pentagon's height + isoscel triangle's height

    std::vector<VertexFormat> vertices =
    {
        // Pentagon
        VertexFormat(center + glm::vec3(circumradius * sin(figures::toRadians(-36)), circumradius * cos(figures::toRadians(-36)), 0), color),
        VertexFormat(center + glm::vec3(circumradius * sin(figures::toRadians(-108)), circumradius * cos(figures::toRadians(-108)), 0), color),
        VertexFormat(center + glm::vec3(circumradius * sin(figures::toRadians(-180)), circumradius * cos(figures::toRadians(-180)), 0), color),
        VertexFormat(center + glm::vec3(circumradius * sin(figures::toRadians(-252)), circumradius * cos(figures::toRadians(-252)), 0), color),
        VertexFormat(center + glm::vec3(circumradius * sin(figures::toRadians(-324)), circumradius * cos(figures::toRadians(-324)), 0), color),
        // Star
        VertexFormat(center + glm::vec3(0, starCircumradius, 0), color),
        VertexFormat(center + glm::vec3(starCircumradius * sin(figures::toRadians(-72)), starCircumradius * cos(figures::toRadians(-72)), 0), color),
        VertexFormat(center + glm::vec3(starCircumradius* sin(figures::toRadians(-144)), starCircumradius * cos(figures::toRadians(-144)), 0), color),
        VertexFormat(center + glm::vec3(starCircumradius * sin(figures::toRadians(-216)), starCircumradius * cos(figures::toRadians(-216)), 0), color),
        VertexFormat(center + glm::vec3(starCircumradius * sin(figures::toRadians(-288)), starCircumradius * cos(figures::toRadians(-288)), 0), color)
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        0, 7, 9,
        1, 8, 5,
        6, 2, 9
    };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;
}

Mesh *figures::CreateEnemy(const std::string &name, glm::vec3 centerOfGravity, float hexagonRadius, glm::vec3 outerColor, glm::vec3 innerColor, bool fill) {
    
    glm::vec3 center = centerOfGravity;
    float radius = hexagonRadius;
    float inner_radius = 0.8 * hexagonRadius;

    std::vector<VertexFormat> vertices =
    {
        // outer hexagon
        VertexFormat(center, outerColor),
        VertexFormat(center + glm::vec3(0, radius, 0), outerColor),
        VertexFormat(center + glm::vec3(radius * sin(figures::toRadians(-60)), radius * cos(figures::toRadians(-60)), 0), outerColor),
        VertexFormat(center + glm::vec3(radius * sin(figures::toRadians(-120)), radius * cos(figures::toRadians(-120)), 0), outerColor),
        VertexFormat(center + glm::vec3(radius * sin(figures::toRadians(-180)), radius * cos(figures::toRadians(-180)), 0), outerColor),
        VertexFormat(center + glm::vec3(radius * sin(figures::toRadians(-240)), radius * cos(figures::toRadians(-240)), 0), outerColor),
        VertexFormat(center + glm::vec3(radius * sin(figures::toRadians(-300)), radius * cos(figures::toRadians(-300)), 0), outerColor),
        // inner hexagon
        VertexFormat(center, innerColor),
        VertexFormat(center + glm::vec3(0, inner_radius, 0), innerColor),
        VertexFormat(center + glm::vec3(inner_radius * sin(figures::toRadians(-60)), inner_radius * cos(figures::toRadians(-60)), 0), innerColor),
        VertexFormat(center + glm::vec3(inner_radius * sin(figures::toRadians(-120)), inner_radius * cos(figures::toRadians(-120)), 0), innerColor),
        VertexFormat(center + glm::vec3(inner_radius * sin(figures::toRadians(-180)), inner_radius * cos(figures::toRadians(-180)), 0), innerColor),
        VertexFormat(center + glm::vec3(inner_radius * sin(figures::toRadians(-240)), inner_radius * cos(figures::toRadians(-240)), 0), innerColor),
        VertexFormat(center + glm::vec3(inner_radius * sin(figures::toRadians(-300)), inner_radius * cos(figures::toRadians(-300)), 0), innerColor)
    };

    Mesh* enemy = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        // inner hexagon
        7, 8, 9,
        7, 9, 10,
        7, 10, 11,
        7, 11, 12,
        7, 12, 13,
        7, 13, 8,
        // outer hexagon
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 5,
        0, 5, 6,
        0, 6, 1
    };

    if (!fill) {
        enemy->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    enemy->InitFromData(vertices, indices);
    return enemy; 
}

Mesh *figures::CreateHeart(const std::string &name, glm::vec3 centerOfGravity, float heartHeight, glm::vec3 color, bool fill) {

    glm::vec3 corner = centerOfGravity;
    float heartWidth = heartHeight / 1.2; 

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color),
        VertexFormat(corner + glm::vec3(-heartWidth/2, heartWidth/2, 0), color),
        VertexFormat(corner + glm::vec3(-heartWidth, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, -heartHeight, 0), color),
        VertexFormat(corner + glm::vec3(heartWidth, 0, 0), color),
        VertexFormat(corner + glm::vec3(heartWidth/2, heartWidth/2, 0), color)
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        0, 1, 2, 
        0, 2, 3,
        0, 3, 4,
        0, 4, 5
    };

    if (!fill) {
        heart->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    heart->InitFromData(vertices, indices);
    return heart;
}

 Mesh *figures::CreateSun(const std::string &name, glm::vec3 centerOfGravity, float sunRadius, float octagonRadius, glm::vec3 innerColor, glm::vec3 outerColor, bool fill) {

    glm::vec3 center = centerOfGravity;

    std::vector<VertexFormat> vertices =
    {
        // Sunshine vertices 
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-22)), sunRadius * cos(figures::toRadians(-22)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-67.5)), sunRadius * cos(figures::toRadians(-67.5)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-112.5)), sunRadius * cos(figures::toRadians(-112.5)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-157.5)), sunRadius * cos(figures::toRadians(-157.5)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-202.5)), sunRadius * cos(figures::toRadians(-202.5)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-247.5)), sunRadius * cos(figures::toRadians(-247.5)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-292.5)), sunRadius * cos(figures::toRadians(-292.5)), 0), outerColor),
        VertexFormat(center + glm::vec3(sunRadius * sin(figures::toRadians(-337.5)), sunRadius * cos(figures::toRadians(-337.5)), 0), outerColor),
        // Octagon
        VertexFormat(center + glm::vec3(0, octagonRadius, 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-45)), octagonRadius * cos(figures::toRadians(-45)), 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius* sin(figures::toRadians(-90)), octagonRadius * cos(figures::toRadians(-90)), 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-135)), octagonRadius * cos(figures::toRadians(-135)), 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-180)), octagonRadius * cos(figures::toRadians(-180)), 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-225)), octagonRadius * cos(figures::toRadians(-225)), 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-270)), octagonRadius * cos(figures::toRadians(-270)), 0), innerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-315)), octagonRadius * cos(figures::toRadians(-315)), 0), innerColor),
        VertexFormat(center, innerColor),
        // Sunshine Octagon 
        VertexFormat(center + glm::vec3(0, octagonRadius, 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-45)), octagonRadius * cos(figures::toRadians(-45)), 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius* sin(figures::toRadians(-90)), octagonRadius * cos(figures::toRadians(-90)), 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-135)), octagonRadius * cos(figures::toRadians(-135)), 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-180)), octagonRadius * cos(figures::toRadians(-180)), 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-225)), octagonRadius * cos(figures::toRadians(-225)), 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-270)), octagonRadius * cos(figures::toRadians(-270)), 0), outerColor),
        VertexFormat(center + glm::vec3(octagonRadius * sin(figures::toRadians(-315)), octagonRadius * cos(figures::toRadians(-315)), 0), outerColor),
    };

    Mesh* sun = new Mesh(name);
    std::vector<unsigned int> indices = 
    { 
        // Sunshine
        0, 18, 17,
        19, 18, 1,
        20, 19, 2,
        21, 20, 3,
        22, 21, 4,
        23, 22, 5,
        24, 23, 6,
        17, 24, 7,
        // Octagon
        16, 8, 9,
        16, 9, 10,
        16, 10, 11,
        16, 11, 12,
        16, 12, 13,
        16, 13, 14,
        16, 14, 15,
        16, 15, 8,

    };

    if (!fill) {
        sun->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    sun->InitFromData(vertices, indices);
    return sun;
 }