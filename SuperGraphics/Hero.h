#pragma once
#include "Primitives.h"
#include "directions.h"
#include "Model.h"
class Hero : public Model
{
public:
	int direction;
	vec3 lastPos;
	float jumpStep = 0.01f, moveStep = 0.03f;
	Hero() {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(-1.f, 1.f, 0.f), vec3(0.f), vec3(1.2f)),
		};

	}
	void update() {
		if (direction == (int)Up) {
			primitives[0]->position += vec3(0.f, jumpStep, 0.f);
			if ( primitives[0]->position.y- lastPos.y > 100*jumpStep) {
				direction = (int)Down;
			}
		}
		else if (direction == (int)Down) {
			primitives[0]->position -= vec3(0.f, jumpStep, 0.f);
			if ( primitives[0]->position.y - lastPos.y  == 0.f) {
				direction = ' ';
			}
		}
		else if (direction == (int)Left) {
			primitives[0]->position -= vec3(moveStep, 0.f, 0.f);
			direction = ' ';			
		}
		else if (direction == (int)Right) {
			primitives[0]->position += vec3(moveStep, 0.f, 0.f);
			direction = ' ';
		}
	}

	void setDir(int  dir) {
		if (dir != direction) {
			lastPos = primitives[0]->position;
		}
		direction = dir;
	}

	void handelInput(GLFWwindow *Window) {
		if (glfwGetKey(Window, GLFW_KEY_I) == GLFW_PRESS) {
			this->setDir((int)Up);
		}
		if (glfwGetKey(Window, GLFW_KEY_J) == GLFW_PRESS) {
			this->setDir((int)Left);
		}
		if (glfwGetKey(Window, GLFW_KEY_L) == GLFW_PRESS) {
			this->setDir((int)Right);
		}	
	}
	~Hero();
};
