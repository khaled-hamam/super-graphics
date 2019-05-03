#pragma once
#include <vector>
#include <time.h>
#include "Model.h"
#include "Models.h"
#include "Skybox.h"
using namespace std;
using namespace glm;

#define SPIKE_COUNT 4
#define SPIKE_DIFFICULTY 20
#define VILLAIN_DIFFICULTY 20
#define SMART_ENEMY_DIFFICULTY 90
#define POWERUP_DIFFICULTY 30
#define COIN_DIFFICULTY 20
#define FLYING_BLOCK_DIFFICULTY 20
#define FIRE_BLOCK_DIFFICULTY 50
#define FLYING_BLOCK_TYPES 2

struct Level {
    Skybox *skybox;
    DirectionalLight *sun;
    Hero *hero;
    vector<Model *> world;

    ~Level() {
        delete skybox;
        delete sun;
        delete hero;
        for (auto i : world) {
            delete i;
        }
        world.clear();
    }
};

enum LevelEffect {
    NO_EFFECT,
    NORMAL_EFFECT,
    INVERSE_EFFECT
};

class LevelGenerator {
private:
    static LevelGenerator *instance;
    int currentLevel = 0;
    int remainingSpikes = 0;

    Model* nextGroundBlock(vec3 nextPosition) {
        Model *nextBlock;
        int choose = shouldMakeObject(SPIKE_DIFFICULTY, NORMAL_EFFECT);

        if ((choose || remainingSpikes) && nextPosition.y == 0 && nextPosition.x > 5) {
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
                int choose = shouldMakeObject(VILLAIN_DIFFICULTY, NORMAL_EFFECT);
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
                int choose = shouldMakeObject(SMART_ENEMY_DIFFICULTY, NORMAL_EFFECT);
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
                int choose = shouldMakeObject(POWERUP_DIFFICULTY, INVERSE_EFFECT);
                if (choose) {
                    level.push_back(new PowerUp(vec3(i, ending.y + 1, k)));
                }
            }
        }
    }

    void generateCoins(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(COIN_DIFFICULTY, NO_EFFECT);
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
				int choose = shouldMakeObject(FIRE_BLOCK_DIFFICULTY, NORMAL_EFFECT);
				if (choose) {
					level.push_back(new FireBlock(vec3(i, ending.y, k)));
				}
			}
		}
	}

    void generateFlyingBlocks(vector<Model*> &level, vec3 start, vec3 ending) {
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                int choose = shouldMakeObject(FLYING_BLOCK_DIFFICULTY, NO_EFFECT);
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

    bool shouldMakeObject(int difficulty, LevelEffect effect) {
        bool shouldMake = false;

        switch (effect)
        {
        case NO_EFFECT:
            shouldMake = rand() % difficulty == 0;
            break;
        case NORMAL_EFFECT:
            if (difficulty / this->currentLevel == 0) {
                shouldMake = true;
            }
            else {
                shouldMake = rand() % (difficulty / this->currentLevel) == 0;
            }
            break;
        case INVERSE_EFFECT:
            shouldMake = rand() % (difficulty * this->currentLevel) == 0;
            break;
        }

        return shouldMake;
    }

public:
    Level level;

    static LevelGenerator *getInstance();

    Level* generateLevel(bool nextLevel = true, vec3 start = vec3(-2.f, -1.f, -1.f), vec3 ending = vec3(300.f, 0.f, 0.f)) {
        if (nextLevel) {
            this->currentLevel++;
        }
        srand(time(NULL));
        Light::clearLights();

        if (!level.skybox)
            level.skybox = new Skybox();
        if (currentLevel % 2 == 0) {
            level.skybox->setNightMode();
        }

        if (!level.hero) {
            level.hero = new Hero(vec3(ending.z, ending.y + 1.f, start.x + 2));
        } else {
            vec3 delta = level.hero->position - vec3(ending.z, ending.y + 1.f, start.x + 2);
            level.hero->light = new PointLight();
            level.hero->move(-delta);
            level.hero->lives = 3;
        }

        if (!level.sun)
            level.sun = new DirectionalLight();
        level.sun->use();

        level.world.clear();

        // Setting Ground Blocks (Blocks / Spikes)
        for (GLfloat i = start.x; i <= ending.x; ++i) {
            for (GLfloat j = start.y; j <= ending.y; ++j) {
                for (GLfloat k = start.z; k <= ending.z; ++k) {
                    if (i < 5) {
                        level.world.push_back(new Block(vec3(i, j, k)));
                    } else {
                        level.world.push_back(this->nextGroundBlock(vec3(i, j, k)));
                    }
                }
            }
        }

        // Setting Next Level Portals
        auto callback = []() {
            LevelGenerator *generator = LevelGenerator::getInstance();
            generator->generateLevel();
        };

        for (int j = 1; j <= 3; ++j) {
            for (GLfloat k = start.z; k <= ending.z; ++k) {
                level.world.push_back( new NextLevelPortal(callback, vec3(ending.x, ending.y + j, k)));
            }
        }
        level.world.push_back(new NextLevelPortal(callback, vec3(6, ending.y + 1, 0)));

        // Seeding the World
        start.x += 5;
        ending.x -= 5;
        this->generatePowerups(level.world, start, ending);
        this->generateFlyingBlocks(level.world, start, ending);
        this->generateFireBlocks(level.world, start, ending);
        this->generateVillains(level.world, start, ending);
        this->generateSmartEnemies(level.world, start, ending);
        this->generateCoins(level.world, start, ending);

        return &this->level;
    }

    int getCurrentLevel() {
        return this->currentLevel;
    }
};