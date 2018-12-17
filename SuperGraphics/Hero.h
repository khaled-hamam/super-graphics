#pragma once
#include "Primitives.h"
#include "directions.h"
#include "Model.h"
class Hero : public Model
{
public:
	int lives = 3;
	Directions direction = STATIC;
	vec3 lastPos;
	float jumpStep = 0.1f, moveStep = 0.1f;
    int lives = 3;
    double lastHitTime = 0;

    bool isImmune() {
        return glfwGetTime() - lastHitTime >= 3000;
    }

    void decreaseLives() {
        if (isImmune() == false) {
            lastHitTime = glfwGetTime();
            lives -= 1;
        }
    }

	Hero(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(0.f, 0.f, 0.f), vec3(0.f), vec3(1.f)),
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);

	}
	void update() {
		if (direction == UP) {
			this->move(vec3(0.f, jumpStep, 0.f));
			if (this->position.y - lastPos.y > 2.25) {
				direction = DOWN;
			}
		} else if (direction == DOWN) {
            this->move(vec3(0.f, -moveStep, 0.f));
            if (this->position.y - lastPos.y == 0) {
                direction = STATIC;
            }
        } else {
			this->move(vec3(0.f, -moveStep, 0.f));
		}
	}
     
	void handelInput(GLFWwindow *Window) {
		if (glfwGetKey(Window, GLFW_KEY_I) == GLFW_PRESS && direction == STATIC) {
			lastPos = this->position;
			direction = UP;
		}
		if (glfwGetKey(Window, GLFW_KEY_J) == GLFW_PRESS) {
			this->move(vec3(-moveStep, 0.f, 0.f));
		}
		if (glfwGetKey(Window, GLFW_KEY_L) == GLFW_PRESS) {
			this->move(vec3(moveStep, 0.f, 0.f));
		}	
	}
	~Hero();
};
