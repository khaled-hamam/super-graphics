#pragma once
#include <vector>
#include <time.h>
#include "Model.h"
#include "Models.h"
using namespace std;
using namespace glm;

#define SPIKE_COUNT 4
#define SPIKE_DIFFICULTY 20
#define VILLAIN_DIFFICULTY 20
#define SMART_ENEMY_DIFFICULTY 50
#define POWERUP_DIFFICULTY 30
#define COIN_DIFFICULTY 20
#define FLYING_BLOCK_DIFFICULTY 20
#define FIRE_BLOCK_DIFFICULTY 30
#define FLYING_BLOCK_TYPES 2

struct Level {
    Skybox *skybox;
    DirectionalLight *sun;
    Hero *hero;
    vector<Model *> world;
};

class LevelGenerator {
private:
    int currentLevel = 0;
    int remainingSpikes = 0;

    Model* nextGroundBlock(vec3 nextPosition) {
        Model *nextBlock;
        int choose = shouldMakeObject(SPIKE_DIFFICULTY);

        if ((choose || remainingSpikes) && nextPosition.y == 0) {
            nextBlock = new Spike(nextPosition);
            if (!remainingSpikes) {
                remainingSpikes = SPIKE_COUNT - 1;
            } else {
                remainingSpikes--;
            }
        } else {
            nextBlock = new Block(nextPosition);
        }

        return nextBlock;
    }

    void generateVillains(vector<Model*> &level, vec3 start, vec3 ending) {
        if (this->currentLevel > 3)
            return;

        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(VILLAIN_DIFFICULTY);
                if (choose) {
                    level.push_back(new Villian(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

    void generateSmartEnemies(vector<Model*> &level, vec3 start, vec3 ending) {
        if (this->currentLevel < 3)
            return;

        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(SMART_ENEMY_DIFFICULTY);
                if (choose) {
                    level.push_back(new SmartEnemy(this->level.hero, vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

    void generatePowerups(vector<Model*> &level, vec3 start, vec3 ending) {
        if (this->currentLevel > 3)
            return;

        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(POWERUP_DIFFICULTY);
                if (choose) {
                    level.push_back(new PowerUp(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

    void generateCoins(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(COIN_DIFFICULTY);
                if (choose) {
                    level.push_back(new Coin(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

	void generateFireBlocks(vector<Model*> &level, vec3 start, vec3 ending) {
        if (this->currentLevel < 2)
            return;

		for (GLfloat i = start.x; i <= ending.x; ++i) {
			for (GLfloat k = start.z; k <= ending.z; ++k) {
				int choose = shouldMakeObject(FIRE_BLOCK_DIFFICULTY);
				if (choose) {
					level.push_back(new FireBlock(vec3(i, ending.y + 1, k)));
				}
			}
		}
	}

    void generateFlyingBlocks(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(FLYING_BLOCK_DIFFICULTY);
                int blockType = rand() % FLYING_BLOCK_TYPES;

                if (choose) {
                    switch (blockType)
                    {
                    case 0:
                        level.push_back(new WoodenBox(vec3(i, ending.y + 2, k)));
                        break;
                    case 1:
                        level.push_back(new Obstacle(vec3(i, ending.y + 2, k)));
                        break;
                    }
                }
            }
        }
    }

    bool shouldMakeObject(int difficulty) {
        if (difficulty / this->currentLevel == 0) {
            return true;
        } else {
            return rand() % (difficulty / this->currentLevel) == 0;
        }
    }

public:
    Level level;

    Level* generateLevel(bool nextLevel = true, vec3 start = vec3(-2.f, -1.f, -1.f), vec3 ending = vec3(300.f, 0.f, 0.f)) {
        if (nextLevel) {
            this->currentLevel++;
        }
        srand(time(NULL));

        level.skybox = new Skybox();
        level.hero = new Hero(vec3(ending.z, ending.y + 1.f, start.x + 2));
        level.sun = new DirectionalLight();


        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat j = start.y; j <= ending.y; ++j) {
                for (GLfloat k = start.z; k <= ending.z; ++k) {
                  level.world.push_back(this->nextGroundBlock(vec3(i, j, k)));
                }
            }
        }

        this->generatePowerups(level.world, start, ending);
        this->generateFlyingBlocks(level.world, start, ending);
        this->generateFireBlocks(level.world, start, ending);
        this->generateVillains(level.world, start, ending);
        this->generateSmartEnemies(level.world, start, ending);
        this->generateCoins(level.world, start, ending);

        return &this->level;
    }
};