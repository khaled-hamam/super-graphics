#pragma once
#include "Model.h"
#include "Primitives.h"
class Spike : public Model
{
public:
	Spike() {

		

		GLfloat x = 4;
		while (x <= 5) {
			primitives.push_back(new Pyramid(nullptr, vec3(x, 0.55f, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.2f), vec3(BLUE)));
			x+=0.1f;
		}
	}

	void update(){}
	~Spike();
};

