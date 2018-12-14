#pragma once
#include "Primitives.h"
#include "Model.h"
class Villian : public Model
{
public:
	int count = 0;
	Directions dir = LEFT;

	Villian() {
		primitives = {
			new Quad(nullptr, vec3(7.f, 0.6f, 0.f), vec3(0.f), vec3(0.2f)),
		};
	}

	void update() {
		if (count != 100 && dir == LEFT) {
			cout << "left";
			primitives[0]->position -= vec3(0.01f, 0.f, 0.f);
			count++;
			if (count == 100) {
				dir = RIGHT;
				count = 0;
			}
		}
		else if (count != 100 && dir == RIGHT) {
			cout << "right";
			primitives[0]->position += vec3(0.01f, 0.f, 0.f);
			count++;
			if (count == 100) {
				dir = LEFT;
				count = 0;
			}
		}
	}
	~Villian();
};
