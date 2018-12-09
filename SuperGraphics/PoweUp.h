#pragma once
#include "Model.h"
#include "Primitives.h"

class PowerUp : public Model {
public:
	PowerUp() {
		primitives = {
			new Pyramid(ResourceManager::getTexture(""),vec3(1.0f, -0.6f, 0.f),vec3(0.f, 0.f, 0.f), vec3(0.3f),vec3(GREEN)),
			new Pyramid(ResourceManager::getTexture(""),vec3(0.9f, -0.5f, 0.f),vec3(0.f, 0.f, 180.f), vec3(0.1f),vec3(GREEN)),
			new Pyramid(ResourceManager::getTexture(""),vec3(1.1f, -0.5f, 0.f),vec3(0.f, 0.f, 180.f), vec3(0.1f),vec3(GREEN)),

		};
	}
	void update() {
		primitives[0]->rotation += vec3(0.f, 1.0f, 0.f);
		primitives[1]->rotation += vec3(0.f, -1.0f, 0.f);
		primitives[2]->rotation += vec3(0.f, -1.0f, 0.f);

	}
};