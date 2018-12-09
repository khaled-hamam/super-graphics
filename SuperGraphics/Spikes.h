#pragma once
#include "Model.h"
#include "Primitives.h"
class Spikes : public Model
{
public:
	Spikes() {

		GLfloat x = 4;
		while (x <= 5) {
			primitives.push_back(new Triangle(ResourceManager::getTexture(""), vec3(x, 0.5f, 0.5f), vec3(0.f, 0.f, 0.f), vec3(0.6f)));
			x+=0.2f;
		}
	}

	void update(){}
	~Spikes();
};

