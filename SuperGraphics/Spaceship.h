#pragma once
#include "Model.h"
#include "Primitives.h"
class Spaceship : public Model
{
public:
	int count = 0;
	Directions dir = UP;
	float step = 0.01;
	Spaceship(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Quad(ResourceManager::getTexture("spaceship"), vec3(0.f, 0.f, 0.f), vec3(0.f), vec3(1.f))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);

	}
	void update() {
		if (count != 50 && dir == UP) {
			primitives[0]->position += vec3(0.f, step, 0.f);
			count++;
			if (count == 50) {
				dir = DOWN;
				count = 0;
			}
		}
		else if (count != 50 && dir == DOWN) {
			primitives[0]->position -= vec3(0.0f, step, 0.f);
			count++;
			if (count == 50) {
				dir = UP;
				count = 0;
			}
		}

	}
	~Spaceship();
};

