#pragma once
#pragma once
#include "Model.h"
#include "Primitives.h"
class WoodenBox : public Model
{
public:
	int count = 0;
	float step = 0.01;
	Directions dir = UP;
	WoodenBox(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Cube(ResourceManager::getTexture("box"), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}

	void update() {
		if (count != 50 && dir == UP) {
			this->move(vec3(0.f, step, 0.f));
			count++;
			if (count == 50) {
				dir = DOWN;
				count = 0;
			}
		}
		else if (count != 50 && dir == DOWN) {
			this->move(vec3(0.f, -step, 0.f));
			count++;
			if (count == 50) {
				dir = UP;
				count = 0;
			}
		}
	}
	virtual void collision(Model *hero, Directions directions, float distance) override  {
		if (directions == UP) {
			this->move(vec3(0.f, distance, 0.f));
		}
		else if (directions == LEFT) {
			this->move(vec3(-distance, 0.f, 0.f));
		}
		else if (directions == RIGHT) {
			this->move(vec3(distance, 0.f, 0.f));
		}
	}
	~WoodenBox();
};

