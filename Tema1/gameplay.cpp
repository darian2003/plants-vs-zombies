#include <iostream>
#include "lab_m1/Tema1/Tema1.h"
#include <cstdlib>
#include<iterator>

#include "core/engine.h"
#include "utils/gl_utils.h"

using namespace std;
using namespace m1;

void Tema1::initMatrix() {
        matrix = new GrassSquare*[3];
        for (int i = 0; i < 3; ++i) {
        matrix[i] = new GrassSquare[3];
     }

    for (int i = 0 ; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float cx = 10 + redRectangleLength + gridGap + greenSquareSide/2 + (greenSquareSide + gridGap) * j;
            float cy = 20 + greenSquareSide/2 + (greenSquareSide + gridGap) * (2-i);
            matrix[i][j].GrassSquare::set(true, cx, cy, i, j, greenSquareSide);
        }
    }
}

int Tema1::spawnEnemy(float enemySpawnTime) {

    // TODO CHANGE THIS
    if (rand() % (int)enemySpawnTime == 0) {
        int enemyLine = rand() % 3;
        float y = levelMap.find(enemyLine)->second;
        float x = 1300;
        map<string, glm::vec3>::iterator it = colorMap.begin();
        int colorOffset = rand() % 4;
        std::string color = next(it, colorOffset)->first;
        enemyLines[enemyLine].push_back(new Enemy(color, enemyLine, x, y));
        return 1;
    }
    return 0;
}

void Tema1::moveEnemies(float deltaTime) {
    float d = deltaTime * 70;
    for (int i = 0; i < 3; i++) {
        for (auto elem : enemyLines[i]) {
            elem->Enemy::setX(elem->Enemy::getX() - d);
        }
    }
}

void Tema1::spawnProjectiles(float deltaTime) {
    for (auto fighter : fighters) {
        if (fighter->Fighter::getScale() < 1 || !fighter->Fighter::checkIfSet()) {
            continue;
        }
        int i = inversedLevelMap[fighter->Fighter::getY()]; // find out which line is the fighter set on
        int ok = 0;
        int distance_check = 0;
        for (auto enemy : enemyLines[i]) {
            if (fighter->Fighter::getColor() == enemy->Enemy::getColor()) {
                ok = 1;
                float distance = enemy->Enemy::getX() - fighter->Fighter::getX();
                if (distance < greenSquareSide / 2) {
                    ok = 2;
                    break;
                }
            }
        }
        if (ok == 1) {
            int tryToShoot = fighter->Fighter::tryToShoot(deltaTime);
            if (tryToShoot ) {
                projectiles[i].push_back(new Projectile(fighter->Fighter::getX()+50, fighter->Fighter::getY(), fighter->Fighter::getColor()));
                printf("PROJECTILE: color = %s at %f %f\n", fighter->Fighter::getColor().c_str(), fighter->Fighter::getX()+30, fighter->Fighter::getY());
            }
        }
    }
}

void Tema1::moveProjectiles(float deltaTime) {
    for (int i = 0; i < 3; i++) {
        int pos = 0;
        for (auto projectile : projectiles[i]) {
            projectile->Projectile::updateXDegree(deltaTime);
            projectile->Projectile::updateX(deltaTime);
            // TODO CHECK COLLISION
            for (auto enemy : enemyLines[i]) {
                if (projectile->Projectile::getColor() == enemy->Enemy::getColor() && enemy->Enemy::getScale() == 1) {
                    if (enemy->Enemy::getX() - projectile->Projectile::getX() + 10 <= starCircumradius + hexagonRadius) {
                        vector<Projectile*>::iterator it;
                        it = projectiles[i].begin() + pos;
                        projectiles[i].erase(it);
                        if (enemy->Enemy::updateHp()) {
                            enemy->Enemy::scaleDown(deltaTime);
                            break;
                        }
                        int color = changeColor();
                        if (color != -1) {
                            auto it = inversedColorMap.begin();
                            while (color > 0) {
                                it++;
                                color--;
                            }
                            enemy->Enemy::setColor(it->second);
                        }
                        break;
                    }
                }
            }
        }
        pos++;
    }
}

void Tema1::scaleDownEntities(float deltaTimeSeconds) {

    for (int i = 0; i < 3; i++) {
        for (auto en = enemyLines[i].begin(); en != enemyLines[i].end(); en++) {
            Enemy *enemy = *en;
            // check if enemies need to be scaled down
            if (enemy->Enemy::getHp() <= 0) {
                enemy->Enemy::scaleDown(deltaTimeSeconds); 
            } else {
                // check if fighters need to be scaled down
                for (auto fighter : fighters) {
                    if (!fighter->Fighter::checkIfSet()) // if fighter is moving along with the cursor, it cant be scaled down
                        continue;
                    int level = inversedLevelMap[fighter->Fighter::getY()];
                    float distance  = enemy->Enemy::getX() - fighter->Fighter::getX();
                    // last condition assures us that we can stil place a fighter on a square even if an enemy is past that square (to the left of the fighter)
                    if (level == i && distance <= greenSquareSide / 2 + hexagonRadius - 10 && -distance <= greenSquareSide / 2) { 
                        fighter->Fighter::scaleDown(deltaTimeSeconds);
                    }
                }
            }
        }
    }
    // scale down fighters that are already in the process of downscaling
    for (auto fighter : fighters) {
        // check if fighters need to be scaled down
        if (fighter->Fighter::getScale() < 1) {
            fighter->Fighter::scaleDown(deltaTimeSeconds);
            
        }
    }
}

void Tema1::deleteEntities() {
    for (auto i = fighters.begin(); i != fighters.end(); ++i) {
        // check if fighters need to be deleted
        Fighter *fighter = *i;
        if (fighter->Fighter::getScale() == 0) {
            printf("UNSET FIGHTER %d %d\n", inversedColumnMap[fighter->Fighter::getX()], inversedLevelMap[fighter->Fighter::getY()]);
            fighters.erase(i);
            i--;
            matrix[inversedLevelMap[fighter->Fighter::getY()]][inversedColumnMap[fighter->Fighter::getX()]].GrassSquare::unsetFighter();
        }
    }

    for (int i = 0; i < 3; i++) {
        for (auto it = enemyLines[i].begin(); it != enemyLines[i].end(); ++it) {
            // check if enemies need to be deleted
            Enemy *enemy = *it;
            if (enemy->Enemy::getScale() == 0) {
                enemyLines[i].erase(it);
                it--;
            }
        }
    }
}

void Tema1::checkIfEnemyReachedFinish() {
    for (int i = 0; i < 3; i++) {
        for (auto en : enemyLines[i]){ 
            if (en->getX() <= leftBorder + redRectangleLength / 2) {
                en->Enemy::setScale(0); // equivalent with delete
                lives--;
            }
        }
    }
}

Fighter* Tema1::getFighter(float x, float y) {
    for (auto elem : fighters) {
        if (elem->Fighter::getX() == x && elem->Fighter::getY() == y)
            return elem;
    }
    return NULL;
}

void Tema1::spawnSun(float sunSpawnTime) {
    // TODO CHANGE THIS
    int spawnTime = (int)sunSpawnTime;
    if (rand() % spawnTime == 0) {
        
        float targetX = float(rand() % 1280);
        float targetY = float(rand() % 720);
        sunVector.push_back(new Sun(targetX, targetY));
    }
}

void Tema1::deleteSun() {
    for (auto it = sunVector.begin(); it != sunVector.end(); ++it) {
        // check if sunshines need to be deleted
        Sun* elem = *it;
        if (elem->Sun::getCollected() == true) {
            sunVector.erase(it);
            it--;
        }
    }
}

void Tema1::sunFall(float deltaTime) {
    for (auto i : sunVector) {
        i->Sun::sunFallEffect(deltaTime);
    }
}

int Tema1::changeColor() {
    if (rand() % 3 == 0) {
        return rand() % 4;
    }
    return -1;
}

