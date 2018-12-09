#pragma once
#include "Model.h"
#include "Primitives.h"
class Block : public Model
{
public:
	Block() {
		GLfloat x = -2;
		while(x < 30){
			GLfloat y = 0;
			while (y > -3) {
				primitives.push_back(new Cube(ResourceManager::getTexture("brownBlock"), vec3(x, y, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f)));
				y--;
			}
			x++;
		}
	
	}
	
	void update(){}
	~Block();
};

