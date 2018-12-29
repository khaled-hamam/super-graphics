#pragma once
#include "Model.h"
#include "Hero.h"
#include "Primitives.h"
class FireBlock : public Model
{
public:
	int count = 0;
	Directions dir = UP;
	float step = 0.01;
	Light *point;

	FireBlock(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Cube(ResourceManager::getTexture("lava"), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
		point = new PointLight();
	}

	void update() {
		((PointLight *)point)->position = this->position;
        float redValue = max(pow(sin(glfwGetTime()), 2), 0.6);
		((PointLight *)point)->ambient = vec3(redValue, 0.3f, 0.3f);
		((PointLight *)point)->diffuse = vec3(redValue, 0.3f, 0.3f);
		point->use();
	}

	virtual void collision(Model *model, Directions directions, float distance) override {
		Hero *hero = (Hero*)model;
        hero->decreaseLives();
		if (directions == UP) {
			hero->move(vec3(0.f, distance, 0.f));
		}
		else if (directions == LEFT) {
			hero->move(vec3(-distance, 0.f, 0.f));
		}
		else if (directions == RIGHT) {
			hero->move(vec3(distance, 0.f, 0.f));
		}
	}


};