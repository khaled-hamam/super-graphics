#pragma once
#include "Model.h"
#include "Primitives.h"

class PowerUp : public Model {
public:
	PowerUp(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Pyramid(nullptr,vec3(0.f, 0.f, 0.f),vec3(0.f, 0.f, 0.f), vec3(0.2f),vec3(GREEN)),
			new Pyramid(nullptr,vec3(-0.1f, 0.1f, 0.f),vec3(0.f, 0.f, 180.f), vec3(0.05f),vec3(GREEN)),
			new Pyramid(nullptr,vec3(0.1f, 0.1f, 0.f),vec3(0.f, 0.f, 180.f), vec3(0.05f),vec3(GREEN))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}
	void update() {
		primitives[0]->rotation += vec3(0.f, 1.0f, 0.f);
		primitives[1]->rotation += vec3(0.f, -1.0f, 0.f);
		primitives[2]->rotation += vec3(0.f, -1.0f, 0.f);
	}


	virtual void collision(Model *model, Directions directions, float distance) override {
		Hero *hero = (Hero*)model;
		this->destroyed = true;

		if (hero->lives < 3) {
			hero->lives++;
		}

		ResourceManager::playSoundEffect("Audio/powerup.wav");
	}
};