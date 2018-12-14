#pragma once
#pragma once
#include "Model.h"
#include "Primitives.h"
class woodenBox : public Model
{
public:
	int count = 0;
	float step = 0.01;
	Directions dir = UP;
	woodenBox() {
		primitives = {
			new Cube(ResourceManager::getTexture("box"), vec3(0.6, 1.0, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.5f)),
		};
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
			primitives[0]->position -= vec3(0.f, step, 0.f);
			count++;
			if (count == 50) {
				dir = UP;
				count = 0;
			}
		}
	}
	~woodenBox();
};

