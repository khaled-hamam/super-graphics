#pragma once
#include "Primitives.h"
#include "directions.h"
#include "Model.h"
class Hero : public Model
{
public:
	Directions direction = STATIC;
	vec3 lastPos;
	float jumpStep = 0.01f, moveStep = 0.01f;
	Hero(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(1.f, 0.f, 0.f), vec3(0.f), vec3(1.f)),
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);

	}
	void update() {
		if (direction == UP) {
			//this->position += vec3(0.f, jumpStep, 0.f);
			this->move(vec3(0.f, jumpStep, 0.f));
			if ( this->position.y - lastPos.y > 2.25) {
				direction = DOWN;
			}
		}
		else if (direction == DOWN) {
			//primitives[0]->position -= vec3(0.f, jumpStep, 0.f);
			this->move(vec3(0.f, -jumpStep, 0.f));
			if ( this->position.y - lastPos.y  <= 0.f) {
				this->position.y = lastPos.y;
			//	primitives[0]->position.y = lastPos.y;
				direction = STATIC;
			}
		}
		//this->move(primitives[0]->position);
	}

	void handelInput(GLFWwindow *Window) {
		if (glfwGetKey(Window, GLFW_KEY_I) == GLFW_PRESS && direction == STATIC) {
			lastPos = this->position;
			direction = UP;
		}
		if (glfwGetKey(Window, GLFW_KEY_J) == GLFW_PRESS) {
			this->move( vec3(-moveStep, 0.f, 0.f));
		}
		if (glfwGetKey(Window, GLFW_KEY_L) == GLFW_PRESS) {
			this->move(vec3(moveStep, 0.f, 0.f));
		}	
	}
	~Hero();
};
