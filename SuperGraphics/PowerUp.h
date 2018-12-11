#pragma once
#include "Model.h"
#include "Primitives.h"

class PowerUp : public Model {
public:
	PowerUp() {
		primitives = {
			new Pyramid(nullptr,vec3(2.0f, 0.65f, 0.f),vec3(0.f, 0.f, 0.f), vec3(0.2f),vec3(GREEN)),
			new Pyramid(nullptr,vec3(1.9f, 0.75f, 0.f),vec3(0.f, 0.f, 180.f), vec3(0.05f),vec3(GREEN)),
			new Pyramid(nullptr,vec3(2.1f, 0.75f, 0.f),vec3(0.f, 0.f, 180.f), vec3(0.05f),vec3(GREEN)),

		};
	}
	void update() {
		primitives[0]->rotation += vec3(0.f, 1.0f, 0.f);
		primitives[1]->rotation += vec3(0.f, -1.0f, 0.f);
		primitives[2]->rotation += vec3(0.f, -1.0f, 0.f);

	}
};