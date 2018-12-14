#pragma once
#include "Primitives.h"
#include "Model.h"
class Hero : public Model
{
public:
	char direction=' ';
	vec3 currentPos;
	Hero() {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(-1.f, 1.f, 0.f), vec3(0.f), vec3(1.2f)),
		};

	}
	void update() {
		if (direction == 'u') {
			primitives[0]->position += vec3(0.f, 0.01f, 0.f);
			cout << currentPos.y << ' '<<primitives[0]->position.y << ' '<<"UP"<<endl;
			if ( primitives[0]->position.y- currentPos.y > 0.3f) {
				direction = 'd';
			}
		}
		else if (direction == 'd') {
			primitives[0]->position -= vec3(0.f, 0.01f, 0.f);
			cout << currentPos.y << ' ' << primitives[0]->position.y << ' ' << "down" << endl;
			if ( primitives[0]->position.y- currentPos.y  == 0.f) {
				direction = ' ';
			}
		}
		else if (direction == 'l') {
			primitives[0]->position -= vec3(0.01f, 0.f, 0.f);
			cout << currentPos.x << ' ' << primitives[0]->position.x << ' ' << "left" << endl;
				direction = ' ';
			
		}
		else if (direction == 'r') {
			primitives[0]->position += vec3(0.01f, 0.f, 0.f);
			cout << currentPos.x << ' ' << primitives[0]->position.x << ' ' << "right" << endl;
				direction = ' ';
			
		}
	}
	void setDir( char dir) {
		cout << "here" << endl;
		if (dir != direction)
			currentPos = primitives[0]->position;
		direction = dir;
	}
	~Hero();
};
