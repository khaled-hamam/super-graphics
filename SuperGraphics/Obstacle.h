#pragma once
#include "Model.h"
#include "Primitives.h"
class Obstacle : public Model
{
public:
	int ypos = 0, yneg = -1;
	Obstacle() {
		primitives = {
		//	new Cube(ResourceManager::getTexture("box"), vec3(0.6, 1.0, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.5f)),
			new Cube(ResourceManager::getTexture("box1"), vec3(3.5, 1.0, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.5f)),

		};
	}

	void update() {
		if (ypos < 100 && yneg == -1) {
			primitives[0]->position += vec3(0.f, 0.01f, 0.f);
			ypos++;
		}
		if (ypos == 100) {
			ypos = -1;
			yneg = 0;
		}
		if (yneg<100 && ypos == -1) {
			primitives[0]->position -= vec3(0.0f, 0.01f, 0.f);
			yneg++;

		}
		if (yneg == 100)
		{
			yneg = -1;
			ypos = 0;
		}
	}
	~Obstacle();
};

