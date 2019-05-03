#pragma once
#include "Models.h"
#include "Primitives.h"

class SmartEnemy : public Model {
private:
    const float stepSize = 0.025f;
    Hero *hero;

public:
    SmartEnemy(Hero *hero, vec3 position = vec3(0.f), vec3 rotation = vec3(0.f), vec3 scale = vec3(1.f)) {
        this->primitives = {
            new Quad(nullptr, vec3(0.f), vec3(0.f, -45.f, 0.f), vec3(1.f))            
        };

        this->hero = hero;
        this->move(position);
        this->rotate(rotation);
        this->changeScale(scale);
        this->scale = vec3(0.7f, 1.f, 1.f);
    }

    void render() override {
        if (this->destroyed) return;

        for (Primitive *premitive : primitives) {
            string texture[] = { "villain-gold01", "villain-gold02" };
            int index = ((int)(5 * glfwGetTime())) % 2;
            premitive->render(ResourceManager::getTexture(texture[index]));
        }
    }

    void update() {
        float differenceOnX = hero->position.x - this->position.x;
        float differenceOnZ = hero->position.z - this->position.z;

        if (differenceOnZ > 0) {
            this->move(vec3(0.f, 0.f, 1.f));
        } else if (differenceOnZ < 0) {
            this->move(vec3(0.f, 0.f, -1.f));
        } else if (differenceOnX > 0) {
            this->move(vec3(this->stepSize, 0.f, 0.f));
        } else if (differenceOnX < 0) {
            this->move(vec3(-this->stepSize, 0.f, 0.f));
        }
    }

    virtual void collision(Model *model, Directions direction, GLfloat distance) override {
        Hero *hero = (Hero *)model;

        if (direction == UP) {
            this->destroyed = true;
			ResourceManager::playSoundEffect("Audio/killenemy.wav");
        } else {
            if (direction == LEFT) {
			    hero->move(vec3(-distance, 0.f, 0.f));
		    }
		    else if (direction == RIGHT) {
			    hero->move(vec3(distance, 0.f, 0.f));
		    }

            hero->decreaseLives();
        }
    }
};