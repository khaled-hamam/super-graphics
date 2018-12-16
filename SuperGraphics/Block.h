#pragma once
#include "Model.h"
#include "Primitives.h"
class Block : public Model
{
public:
	Block(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
	
		primitives = 
		{
			new Cube(ResourceManager::getTexture("brownBlock"), vec3(0.f,0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f))
		};
				
		move(position);
		rotate(rotaion);
		changeScale(scale);
	}
	
	void update(){}
	virtual void collision(Model *model, Directions directions, float distance) override {
		Hero *hero = (Hero *)model;
		if (directions == UP) {
			hero->move(vec3(0.f, distance, 0.f));
		}
	}
	~Block();
};

