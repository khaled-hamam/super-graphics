#pragma once
#include "Model.h"
#include "Primitives.h"

class Coin : public Model {
public:
	Coin(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(0.3f)) {
		primitives = {
			new Quad(ResourceManager::getTexture("coin"), vec3(0.f, 0.f, 0.f), vec3(0.f), vec3(1.f)),
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}

	void update() {
		primitives[0]->rotation += vec3(0.f, 1.f, 0.f);
	}

	virtual void collision(Model *model, Directions directions, float distance) override {
		Hero *hero = (Hero*)model;
		this->destroyed = true;

		hero->coins++;
		ResourceManager::playSoundEffect("Audio/pickedcoin.wav");
	}
};