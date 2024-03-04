#include "lab_m1/Tema1/Tema1.h"
#include "lab_m1/Tema1/figures.h"

#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

#include "core/engine.h"
#include "utils/gl_utils.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 1280;   // logic width
    logicSpace.height = 720;  // logic height

    glm::vec3 corner = glm::vec3(0, 0, 0);
    initMatrix();

     {
        // Finish Zone
        Mesh *redRectangle = figures::CreateRectangle("red_rectangle", corner, redRectangleLength, redRectangleHeight, glm::vec3(0,0,1), true);
        AddMeshToList(redRectangle);
        visualElements.push_back(new VisualElement("red_rectangle", 10, 20, glm::vec3(0,0,1)));

        // Sun
        Mesh *sun = figures::CreateSun("sun", glm::vec3(0,0,5), sunRadius, octagonRadius, glm::vec3(1,1,0), glm::vec3(1, 0.5, 0), true);
        AddMeshToList(sun);

        // Grey Star = Price
        Mesh *greyStar = figures::CreateStar("grey_star", glm::vec3(0,0,1), greyStarCircumradius, glm::vec3(0.9, 0.9, 0.9), true);
        AddMeshToList(greyStar);

        // Heart
        Mesh *heart = figures::CreateHeart("heart", glm::vec3(0,0,2), heartSize, glm::vec3(1, 0, 0), true);
        AddMeshToList(heart);

        // Green Square
        Mesh *greenSquare = figures::CreateSquare("green_square", corner, greenSquareSide, glm::vec3(0.5,1,0.5), true);
        AddMeshToList(greenSquare);
        float offsetX = 10 + redRectangleLength + gridGap;
        float offsetY = 20;
        for (int line = 0; line < 3; line++) {
            for (int column = 0; column < 3; column++) {
                visualElements.push_back(new VisualElement("green_square", offsetX + greenSquareSide*column + gridGap*column, offsetY + greenSquareSide*line + gridGap*line, glm::vec3(0.5,1,0.5)));
            }
        }

        // Black Box
        Mesh *blackBox = figures::CreateSquare("black_box", corner, greenSquareSide, glm::vec3(0,0,0), false);
        AddMeshToList(blackBox);
    
        
        // Fighters and Stars
        map<std::string, glm::vec3>::iterator colorIt = colorMap.begin();
        while (colorIt != colorMap.end()) {
            std::string coloredRhombus = colorIt->first + "_rhombus";
            std::string coloredStar = colorIt->first + "_star";
            glm::vec3 color = colorIt->second;
            Mesh *rhombus = figures::CreateRhombus(coloredRhombus, glm::vec3(0,0,3), rhombusSide, 60, color, true);
            AddMeshToList(rhombus);
            Mesh *star = figures::CreateStar(coloredStar, glm::vec3(0,0,3), starCircumradius, color, true);
            AddMeshToList(star);
            ++colorIt;
        }

        // Black Box + Fighters + Price
        offsetX = 45;
        colorIt = colorMap.begin();
        map<std::string, int>::iterator priceIt = priceMap.begin();
        for (int column = 0; column < 4; column++) {
            float tx = offsetX + column * (greenSquareSide + offsetX), ty = 700 - greenSquareSide; // coordinates of left bottom corner of the box
            float cx = tx + greenSquareSide/2, cy = ty + greenSquareSide/2; // coordinates for center of the blackbox
            float priceZoneStartX = tx, priceZoneY = ty - 25; // cordinates of price stars
            int price = priceIt->second;
            visualElements.push_back(new VisualElement("black_box", tx, ty, glm::vec3(0.5,1,0.5)));
            BlackBox *black_box = new BlackBox(tx, ty, greenSquareSide, colorIt->first, priceMap[colorIt->first]);
            blackBoxes.push_back(black_box);
            visualElements.push_back(new VisualElement(colorIt->first + "_rhombus", cx, cy, colorIt->second));
            for (int i = 0; i < price; i++) {
                float spaceBetweenStars = greenSquareSide / (price+1);
                visualElements.push_back(new VisualElement("grey_star", priceZoneStartX + spaceBetweenStars*(i+1), priceZoneY, glm::vec3(0.9, 0.9, 0.9)));
            }
            ++colorIt;
            ++priceIt;
        }

        // Enemies
        colorIt = colorMap.begin();
        while (colorIt != colorMap.end()) {
            Mesh *enemy = figures::CreateEnemy(colorIt->first + "_enemy", glm::vec3(0,0,1), hexagonRadius, colorIt->second, glm::vec3(0.25, 0.9, 0.8), true);
            AddMeshToList(enemy);
            ++colorIt;
        }
    }

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.37, 0.37, 0.37, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glLineWidth(3);
    glPointSize(5);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);


    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw - the left half of the window
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.37,0.37,0.37), true);

    // enemy are spawning faster and faster + wave
    if (enemySpawnTime > 200) {
        enemySpawnTime -= 3*deltaTimeSeconds;
    } else {
        enemySpawnTime = 300; // wave is over, reset to standard
    }

    if (sunSpawnTime > 200) {
        sunSpawnTime -= 3*deltaTimeSeconds;
    } else {
        sunSpawnTime = 300; // wave is over, reset to standard
    }

    if (lives == 0){ 
        deltaTimeSeconds = 0;
    }

    spawnEnemy(enemySpawnTime);
    moveEnemies(deltaTimeSeconds);
    moveProjectiles(deltaTimeSeconds);
    spawnProjectiles(deltaTimeSeconds);
    scaleDownEntities(deltaTimeSeconds);
    spawnSun(sunSpawnTime);
    sunFall(deltaTimeSeconds);
    checkIfEnemyReachedFinish();
    deleteEntities();
    deleteSun();

    // Compute the 2D visualization matrix
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);

    DrawScene(visMatrix);
    glDisable(GL_CULL_FACE);
}

void Tema1::DrawScene(glm::mat3 visMatrix)
{

    // Draw sun
    for (auto i : sunVector) {
        modelMatrix = visMatrix * transform2D::Translate(i->Sun::getX(), i->Sun::getY());
        RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
    }

    // Draw hearts
    for (int i = 0; i < lives; i++) {
        BlackBox* lastBlackBox = blackBoxes.back();
        float x = lastBlackBox->BlackBox::getX() + greenSquareSide * 2, y = lastBlackBox->BlackBox::getY() + greenSquareSide * 0.85;
        modelMatrix = visMatrix * transform2D::Translate(x + heartSize * i * 2, y);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    // Draw "wallet"
    {
        BlackBox* lastBlackBox = blackBoxes.back();
        float startX = lastBlackBox->BlackBox::getX() + greenSquareSide * 1.5, startY = lastBlackBox->BlackBox::getY();
        float x = startX, y = startY;
        for (int i = 0; i < money; i++) {
            if (x >= 1270) {
                x = startX;
                y = startY - greyStarCircumradius * 1.5;
            }
            modelMatrix = visMatrix * transform2D::Translate(x, y);
            x += 3 * greyStarCircumradius;
            RenderMesh2D(meshes["grey_star"], shaders["VertexColor"], modelMatrix);
        }
    }

    // Draw enemies
    for (int i = 0; i < 3; i++) {
        for (auto elem : enemyLines[i]) {
            std::string color = elem->Enemy::getColor();
            float scale = elem->Enemy::getScale();
            modelMatrix = visMatrix * transform2D::Translate(elem->Enemy::getX(), elem->Enemy::getY()) * transform2D::Scale(scale, scale);
            RenderMesh2D(meshes[color+"_enemy"], shaders["VertexColor"], modelMatrix);
        }
    }
    
    for (auto i : movingVisualElements) {
        modelMatrix = visMatrix * transform2D::Translate(i->leftBorder, i->bottomBorder);
        RenderMesh2D(meshes[i->name], shaders["VertexColor"], modelMatrix);
    }

    // Draw static elements
    for (auto i : visualElements) {
        modelMatrix = visMatrix * transform2D::Translate(i->leftBorder, i->bottomBorder);
        RenderMesh2D(meshes[i->name], shaders["VertexColor"], modelMatrix);
    }

    // Draw fighters
    for (auto i : fighters) {
        float scale = i->Fighter::getScale();
        modelMatrix = visMatrix * transform2D::Translate(i->Fighter::getX(), i->Fighter::getY()) * transform2D::Scale(scale, scale);
        RenderMesh2D(meshes[i->Fighter::getColor()+"_rhombus"], shaders["VertexColor"], modelMatrix);
    }

    // Draw projectiles
    for (int i = 0; i < 3; i++) {
        for (auto elem : projectiles[i]) {
            std::string color = elem->Projectile::getColor();
            modelMatrix = visMatrix * transform2D::Translate(elem->Projectile::getX(), elem->Projectile::getY()) * transform2D::Rotate(elem->Projectile::getXDegree());
            RenderMesh2D(meshes[color+"_star"], shaders["VertexColor"], modelMatrix);
        }
    }


    // Draw matrix squares    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!matrix[i][j].GrassSquare::isEmpty()) {
                modelMatrix = visMatrix * transform2D::Translate(matrix[i][j].GrassSquare::getCx(), matrix[i][j].GrassSquare::getCy());
            }
        }
    }
}

void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    int mY = 720 - mouseY; 
    if (isSelected) {
        fighters.back()->Fighter::setX(mouseX);
        fighters.back()->Fighter::setY(mY);
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    int mY = 720 - mouseY; 
    if (button == 1) {
        if (!isSelected) {
            // check if sun can be collected
            for (auto i : sunVector) {
                float dX = i->getX() - mouseX, dY = i->getY() - mY;
                float distance = sqrt(pow(dX, 2) + pow(dY, 2));
                if (distance <= octagonRadius) {
                    i->Sun::removeSun();
                    money++;
                    return;
                }
            }

            // check if cursor on black box
            for (auto i : blackBoxes) {
                float size = i->getSize(), x1 = i->getX(), y1 = i->getY(), x2 = x1 + size, y2 = y1 + size;
                std::string color = i->getColor();
                if (mouseX > x1 && mouseX < x2 && mY > y1 && mY < y2) {
                    if (money >= i->getPrice()) {
                        Fighter *fighter = new Fighter(color, mouseX, mY);
                        fighters.push_back(new Fighter(color, mouseX, mY));
                        this->isSelected = true;
                        this->selectedColor = color;
                        this->selectedPrice = i->getPrice();
                    }
                    break;
                }
            }
        } 
    }

    if (button == 2) {
        int mY = 720 - mouseY; 
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                GrassSquare square = matrix[i][j];
                float cx = square.GrassSquare::getCx(), cy = square.GrassSquare::getCy();
                float x1 = cx - greenSquareSide / 2, x2 = x1 + greenSquareSide, y1 = cy - greenSquareSide / 2, y2 = y1 + greenSquareSide; 
                if (mouseX > x1 && mouseX < x2 && mY > y1 && mY < y2) {
                    if (!square.GrassSquare::isEmpty()) {
                        Fighter *fighter = getFighter(cx, cy);
                        fighter->Fighter::setScale(0.99);
                        square.GrassSquare::unsetFighter();
                    }
                    return;

                }
            }
        }
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    int mY = 720 - mouseY; 
    if (button == 1) {
        if (isSelected) {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    float cx = matrix[i][j].GrassSquare::getCx(), cy = matrix[i][j].GrassSquare::getCy(), size = matrix[i][j].GrassSquare::getSquareSide();
                    float x1 = cx - size/2, x2 = cx + size/2, y1 = cy - size/2, y2 = cy + size/2; 
                    if (mouseX < x2 && mouseX > x1 && mY > y1 && mY < y2) {
                        isSelected = false;
                        if (matrix[i][j].GrassSquare::isEmpty()) {
                            fighters.back()->Fighter::setX(cx);
                            fighters.back()->Fighter::setY(cy);
                            fighters.back()->Fighter::setFighter();
                            matrix[i][j].GrassSquare::setFighter();
                            money -= selectedPrice;
                        } else {
                            fighters.pop_back();
                        }
                        return;
                    }
                }
            }
            isSelected = false;
            fighters.pop_back(); 
        }
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
