#pragma once
#include "Model.h"
#include "Primitives.h"
class Obstacle : public Model
{
public:
	Obstacle() {
		primitives = {
			new Cube(ResourceManager::getTexture("box"), vec3(0.6, 1.0, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.5f)),
			new Cube(ResourceManager::getTexture("box1"), vec3(3.5, 1.0, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.5f)),

		};
	}

	void update() {}
	~Obstacle();
};

