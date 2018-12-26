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
#define POWERUP_DIFFICULTY 30
#define COIN_DIFFICULTY 20
#define FLYING_BLOCK_DIFFICULTY 20
#define FLYING_BLOCK_TYPES 2

class LevelGenerator {
private:
    int remainingSpikes = 0;

    Model* nextGroundBlock(vec3 nextPosition) {
        Model *nextBlock;
        int choose = rand() % SPIKE_DIFFICULTY;

        if ((!choose || remainingSpikes) && nextPosition.y == 0) {
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
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = rand() % VILLAIN_DIFFICULTY;
                if (!choose) {
                    level.push_back(new Villian(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

    void generatePowerups(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = rand() % POWERUP_DIFFICULTY;
                if (!choose) {
                    level.push_back(new PowerUp(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

    void generateCoins(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = rand() % COIN_DIFFICULTY;
                if (!choose) {
                    level.push_back(new Coin(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

	void generateFireBlocks(vector<Model*> &level, vec3 start, vec3 ending) {
		for (GLfloat i = start.x; i <= ending.x; ++i) {
			for (GLfloat k = start.z; k <= ending.z; ++k) {
				int choose = rand() % COIN_DIFFICULTY;
				if (!choose) {
					level.push_back(new FireBlock(vec3(i, ending.y + 1, k)));
				}
			}
		}
	}

    void generateFlyingBlocks(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = rand() % FLYING_BLOCK_DIFFICULTY;
                int blockType = rand() % FLYING_BLOCK_TYPES;

                if (!choose) {
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

public:
    vector<Model*> generateLevel(vec3 start = vec3(-2.f, -1.f, -1.f), vec3 ending = vec3(300.f, 0.f, 0.f)) {
        srand(time(NULL));
        vector<Model*> level;

        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat j = start.y; j <= ending.y; ++j) {
                for (GLfloat k = start.z; k <= ending.z; ++k) {
                   level.push_back(this->nextGroundBlock(vec3(i, j, k)));
                }
            }
        }

        this->generatePowerups(level, start, ending);
        this->generateFlyingBlocks(level, start, ending);
		this->generateFireBlocks(level, start, ending);
        this->generateVillains(level, start, ending);
        this->generateCoins(level, start, ending);

        return level;
    }
};