#pragma once
#include "Primitives.h"
#include "Model.h"
class Villian : public Model
{
public:
	int xpos = 0, xneg = -1;
	Villian() {
		primitives = {
			new Quad(nullptr, vec3(7.f, 0.6f, 0.f), vec3(0.f), vec3(0.2f)),
		};
	}

	void update() {
		if (xpos < 100 && xneg == -1) {
			primitives[0]->position += vec3(0.01f, 0.f, 0.f);
			xpos++;
		}
		 if (xpos == 100) {
			xpos = -1;
			xneg = 0;
		}
		 if(xneg<100 &&xpos==-1){
			primitives[0]->position -= vec3(0.01f, 0.f, 0.f);
			xneg++;

		}
		 if (xneg == 100)
		{
			xneg = -1;
			xpos = 0;
		}
	}
	~Villian();
};
