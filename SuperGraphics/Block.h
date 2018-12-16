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
	~Block();
};

