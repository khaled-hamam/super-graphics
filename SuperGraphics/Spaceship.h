#pragma once
#include "Model.h"
#include "Primitives.h"
class Spaceship : public Model
{
public:
	Spaceship() {
		primitives = {
			new Cube(ResourceManager::getTexture("spaceship"), vec3(-1.f, 3.5f, 0.f), vec3(0.f), vec3(3.0f)),
		};
	}
	void update() {
	}
	~Spaceship();
};

