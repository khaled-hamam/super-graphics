#pragma once
#include "Model.h"
#include "Primitives.h"

class Coin : public Model {
public:
	Coin() {
		primitives = {
			new Quad(ResourceManager::getTexture("coin"), vec3(0.5f, 1.f, 0.f), vec3(0.f), vec3(0.3f)),
			new Quad(ResourceManager::getTexture("coin"), vec3(3.5f, 1.f, 0.f), vec3(0.f), vec3(0.3f)),

		};
	}
	void update() {
		primitives[0]->rotation += vec3(0.f, 1.f, 0.f);
		primitives[1]->rotation += vec3(0.f, 1.f, 0.f);

	}
};