#pragma once
#include "Primitives.h"
#include "directions.h"
#include "Model.h"
class Hero : public Model
{
public:
	Directions direction;
	vec3 lastPos;
	float jumpStep = 0.01f, moveStep = 0.03f;
	Hero() {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(-1.f, 1.f, 0.f), vec3(0.f), vec3(1.2f)),
		};

	}
	void update() {
		if (direction == UP) {
			primitives[0]->position += vec3(0.f, jumpStep, 0.f);
			if ( primitives[0]->position.y- lastPos.y > 100*jumpStep) {
				direction = DOWN;
			}
		}
		else if (direction == DOWN) {
			primitives[0]->position -= vec3(0.f, jumpStep, 0.f);
			if ( primitives[0]->position.y - lastPos.y  == 0.f) {
				direction = STATIC;
			}
		}
		else if (direction == LEFT) {
			primitives[0]->position -= vec3(moveStep, 0.f, 0.f);
			direction = STATIC;			
		}
		else if (direction == RIGHT) {
			primitives[0]->position += vec3(moveStep, 0.f, 0.f);
			direction = STATIC;
		}
	}

	void setDir(Directions  dir) {
		if (dir != direction) {
			lastPos = primitives[0]->position;
		}
		direction = dir;
	}

	void handelInput(GLFWwindow *Window) {
		if (glfwGetKey(Window, GLFW_KEY_I) == GLFW_PRESS) {
			this->setDir(UP);
		}
		if (glfwGetKey(Window, GLFW_KEY_J) == GLFW_PRESS) {
			this->setDir(LEFT);
		}
		if (glfwGetKey(Window, GLFW_KEY_L) == GLFW_PRESS) {
			this->setDir(RIGHT);
		}	
	}
	~Hero();
};
