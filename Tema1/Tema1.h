#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema1/visual.h"
#include "lab_m1/Tema1/enemy.h"
#include "lab_m1/Tema1/grass_square.h"
#include "lab_m1/Tema1/black_box.h"
#include "lab_m1/Tema1/fighter.h"
#include "lab_m1/Tema1/projectile.h"
#include "lab_m1/Tema1/sun.h"
#include <cmath>

#include <vector>
#include <map>


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {    
      public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
        Tema1();
        ~Tema1();

        void Init() override;


     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        

        void SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace);
        glm::mat3 VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace);
        void DrawScene(glm::mat3 visMatrix);
        void initMatrix();
        int spawnEnemy(float enemySpawnTime);
        void moveEnemies(float deltaTime);
        void spawnProjectiles(float deltaTime);
        void moveProjectiles(float deltaTime);
        void deleteEntities();
        void scaleDownEntities(float deltaTimeSeconds);
        void checkIfEnemyReachedFinish();
        Fighter *getFighter(float x, float y);
        void spawnSun(float sunSpawnTime);
        void deleteSun();
        void sunFall(float deltaTime);
        int changeColor();

     protected:
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        float greenSquareSide = 130;
        float gridGap = 27;
        float redRectangleLength = 70;
        float redRectangleHeight = 3 * greenSquareSide + 2 * gridGap;
        float leftBorder = 10;
        float bottomBorder = 20;
        float rhombusSide = 60;
        float starCircumradius = 30;
        float greyStarCircumradius = 15;
        float hexagonRadius = 50;
        float enemySqaureSide = 100;
        int money = 10;
        int selectedPrice = 0;
        float gapBetweenHearts = 50;
        float heartSize = 80;
        float sunRadius = 40;
        float octagonRadius = 25;
        float enemySpawnTime = 400;
        float sunSpawnTime = 200;
        std::vector<glm::vec3> rhombusColors = {glm::vec3(1, 1,0), glm::vec3(0.2, 0.2,1), glm::vec3(1, 0.7,0.2), glm::vec3(0.68, 0,1)};
        std::map<std::string, glm::vec3> colorMap = {
           { "orange", glm::vec3(1, 0.5,0) },
           { "blue", glm::vec3(0.2, 0.2,1) },
           { "yellow", glm::vec3(1, 1,0) },
           { "purple", glm::vec3(0.68, 0,1)}
         };

         std::map<std::string, int> priceMap = {
           { "orange", 2 },
           { "blue", 1 },
           { "yellow", 3 },
           { "purple", 2}
         };

          std::map<int, std::string> inversedColorMap = {
           { 0, "orange" },
           { 1, "blue"},
           { 2, "yellow"},
           { 3, "purple"}
         };

         std::map<int, float> levelMap = {
           { 2, bottomBorder + greenSquareSide/2 },
           { 1, bottomBorder + greenSquareSide/2 + greenSquareSide + gridGap },
           { 0, bottomBorder + greenSquareSide/2 + (greenSquareSide + gridGap) * 2 }
         };

         std::map<float, int> inversedLevelMap = {
           { bottomBorder + greenSquareSide/2, 2},
           { bottomBorder + greenSquareSide/2 + greenSquareSide + gridGap, 1},
           { bottomBorder + greenSquareSide/2 + (greenSquareSide + gridGap) * 2, 0}
         };

         std::map<float, int> inversedColumnMap = {
           { 10 + redRectangleLength + gridGap + greenSquareSide/2 + (greenSquareSide + gridGap) * 2, 2},
           { 10 + redRectangleLength + gridGap + greenSquareSide/2 + (greenSquareSide + gridGap), 1},
           { 10 + redRectangleLength + gridGap + greenSquareSide/2, 0}
         };


        std::vector<VisualElement*> visualElements;
        std::vector<VisualElement*> movingVisualElements;
        std::vector<BlackBox*> blackBoxes;
        std::vector<Fighter*> fighters;
        std::vector<Sun*> sunVector;

        GrassSquare **matrix;
        std::vector<Enemy*> enemyLines[3];
        std::vector<Projectile*> projectiles[3];
        int lives = 3;
        bool isSelected = false;
        std::string selectedColor;
         

    };
}   // namespace m1
