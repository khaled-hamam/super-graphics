#pragma once
#include "Model.h"
#include "Primitives.h"

class Coin : public Model {
public:
	Coin(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Quad(ResourceManager::getTexture("coin"), vec3(0.f, 0.f, 0.f), vec3(0.f), vec3(0.3f)),
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}
	void update() {
		primitives[0]->rotation += vec3(0.f, 1.f, 0.f);
	}
};