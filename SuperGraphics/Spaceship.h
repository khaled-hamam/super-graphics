#pragma once
#include "Model.h"
#include "Primitives.h"
class Spaceship : public Model
{
public:
	int ypos = 0, yneg = -1;
	Spaceship() {
		primitives = {
			new Quad(ResourceManager::getTexture("spaceship"), vec3(-1.f, 3.5f, 0.f), vec3(0.f), vec3(3.0f)),
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
	~Spaceship();
};

