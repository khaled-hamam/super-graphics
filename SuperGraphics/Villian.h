#pragma once
#include "Primitives.h"
#include "Model.h"
class Villian : public Model
{
public:
	int count = 0;
	float step = 0.02;
	Directions dir = LEFT;

	Villian(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(0.f)) {
		primitives = {
			new Quad(nullptr, vec3(1.f, 0.f, 0.f), vec3(0.f), vec3(0.f))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}

	void update() {
		if (count != 100 && dir == LEFT) {
			this->move(vec3(-step, 0.f, 0.f));
			count++;
			if (count == 100) {
				dir = RIGHT;
				count = 0;
			}
		}
		else if (count != 100 && dir == RIGHT) {
			this->move(vec3(step, 0.f, 0.f));
			count++;
			if (count == 100) {
				dir = LEFT;
				count = 0;
			}
		}
	}
	~Villian();
};