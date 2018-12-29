#include "LevelGenerator.h"

LevelGenerator* LevelGenerator::instance;

LevelGenerator* LevelGenerator::getInstance() {
    if (!instance) {
        instance = new LevelGenerator();
    }
    return instance;
}
