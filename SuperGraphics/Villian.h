#pragma once
#include "Primitives.h"
#include "Model.h"
class Villian : public Model
{
public:
	int count = 0;
	float step = 0.02;
	Directions dir = LEFT;

	Villian(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
        primitives = {
            new Quad(nullptr, vec3(0.f), vec3(0.f, -45.f, 0.f), vec3(1.f))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
        this->scale = vec3(0.7f, 1.f, 1.f);
	}

    void render() override {
        if (this->destroyed) return;

        for (Primitive *premitive : primitives) {
            string texture[] = {"villain01", "villain02"};
            int index = ((int)(5 * glfwGetTime())) % 2;
            premitive->render(ResourceManager::getTexture(texture[index]));
        }
    }

	void update() {
		//if (count != 100 && dir == LEFT) {
		//	this->move(vec3(-step, 0.f, 0.f));
		//	count++;
		//	if (count == 100) {
		//		dir = RIGHT;
		//		count = 0;
		//	}
		//}
		//else if (count != 100 && dir == RIGHT) {
		//	this->move(vec3(step, 0.f, 0.f));
		//	count++;
		//	if (count == 100) {
		//		dir = LEFT;
		//		count = 0;
		//	}
		//}

        this->move(vec3(0.02 * sin(glfwGetTime()), 0.f, 0.f));
	}


	virtual void collision(Model *model, Directions directions, float distance) override {
		Hero *hero = (Hero *)model;
		if (directions == UP) {
		/*	hero->move(vec3(0.f, distance, 0.f));
			hero->direction = STATIC;*/
			this->destroyed = true;
			ResourceManager::playSoundEffect("Audio/killenemy.wav");
		}
		else if (directions == LEFT) {
			hero->move(vec3(-distance, 0.f, 0.f));
			hero->decreaseLives();
		}
		else if (directions == RIGHT) {
			hero->move(vec3(distance, 0.f, 0.f));
			hero->decreaseLives();
		}

	}

	~Villian();
};
