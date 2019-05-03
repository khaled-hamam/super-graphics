#pragma once
#include "Model.h"
#include "Primitives.h"
class Spike : public Model
{
public:
	Spike(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {

		primitives = {
			new Pyramid(nullptr, vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f), vec3(SILVER))
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}

	void update(){
		
	}
	virtual void collision(Model *model, Directions directions, float distance) override {
		Hero *hero = (Hero*)model;
        if (distance > 0.3f)
		    hero->decreaseLives();
	}
	~Spike();
};

