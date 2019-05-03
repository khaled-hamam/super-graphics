#pragma once
#include "Model.h"
#include "Primitives.h"

class NextLevelPortal : public Model
{
private:
    void (*nextLevelCallback)(void);

public:
    NextLevelPortal(
        void (*nextLevelCallback)(void),
        vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
        primitives = {
            new Cube(ResourceManager::getTexture("portal"), vec3(0.f,0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f))
        };

        this->nextLevelCallback = nextLevelCallback;
        move(position);
        rotate(rotaion);
        changeScale(scale);
    }

    void update() {}

    virtual void collision(Model *model, Directions directions, float distance) override {
        this->nextLevelCallback();
    }

    ~NextLevelPortal();
};

