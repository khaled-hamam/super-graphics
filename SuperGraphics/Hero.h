#pragma once
#include "Primitives.h"
#include "Model.h"
class Hero : public Model
{
public:
	int direction = -1;
	vec3 lastPosition;
	Hero() {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(-1.f, 1.f, 0.f), vec3(0.f), vec3(1.2f)),
		};
	}
	void update() {
		if (direction == 1) {
			primitives[0]->position += vec3(0.0f, 0.01f, 0.f);
			if (primitives[0]->position.y - lastPosition.y >= 5) {
				direction = 3;
			}
		}
		else if (direction == 3) {
			primitives[0]->position -= vec3(0.0f, -0.01f, 0.f);
			if (primitives[0]->position.y == 0) {
				direction = 0;
			}
		}
	}
	void setDir(int dir) {
		direction = dir;
		if (direction != dir) {
			lastPosition = primitives[0]->position;
		}
	}
	~Hero();
};

