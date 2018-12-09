#pragma once
#include "Primitives.h"
#include "Model.h"
class Hero : public Model
{
public:
	Hero() {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(-1.f, 1.f, 0.f), vec3(0.f), vec3(1.2f)),
		};
	}
	void update() {

	}
	~Hero();
};

