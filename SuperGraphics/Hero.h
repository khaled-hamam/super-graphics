#pragma once
#include "Primitives.h"
#include "directions.h"
#include "Model.h"
#include "Lights.h"
#include "ControlScheme.h"

class Hero : public Model
{
private:
    Controls::ControlScheme HeroNormalControl = { GLFW_KEY_SPACE, GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN };
    Controls::ControlScheme HeroFlippedControl = { GLFW_KEY_SPACE, GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_LEFT };

public:
	int lives = 3;
	int coins = 0;
    bool isMoving = false;
	Directions direction = STATIC;
	vec3 lastPos;
	float jumpStep = 0.1f, moveStep = 0.1f;
    double lastHitTime = 0;
	PointLight* light;
    Controls::ControlScheme scheme = this->HeroNormalControl;

    bool isImmune() {
        return glfwGetTime() - lastHitTime <= 3;
    }
	
    void decreaseLives() {
        if (isImmune() == false) {
            lastHitTime = glfwGetTime();
            lives -= 1;
			ResourceManager::playSoundEffect("Audio/crash.wav");
		}
    }

	Hero(vec3 position = vec3(0.f), vec3 rotaion = vec3(0.f), vec3 scale = vec3(1.f)) {
		primitives = {
			new Quad(ResourceManager::getTexture("hero"), vec3(0.f), vec3(0.f, -45.f, 0.f), vec3(1.f)),
		};
		move(position);
		rotate(rotaion);
		changeScale(scale);
		light = new PointLight();
        this->scale = vec3(0.7f, 1.f, 1.f);
	}

    void render() override {
        ((PointLight*)light)->position = this->position;
        ((PointLight*)light)->use();

        if (isMoving) {
            string texture[6];
            for (int i = 1; i <= 6; ++i) {
                texture[i - 1] = "alien_run_" + to_string(i);
            }

            double time = glfwGetTime();
            double decimal = time - (int)time;
            int index = min(6 * decimal, 5.0);
            for (auto primitive : primitives) {
                primitive->render(ResourceManager::getTexture(texture[index]));
            }
        } else {
            string texture[3];
            for (int i = 1; i <= 3; ++i) {
                texture[i - 1] = "alien_idle_" + to_string(i);
            }

            double time = glfwGetTime();
            double decimal = time - (int)time;
            int index = min(3 * decimal, 2.0);
            for (auto primitive : primitives) {
                primitive->render(ResourceManager::getTexture(texture[index]));
            }
        }
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
        bool shouldMove = false;

		if (glfwGetKey(Window, scheme.Jump) == GLFW_PRESS && direction == STATIC) {
			lastPos = this->position;
			direction = UP;
			ResourceManager::playSoundEffect("Audio/jump.ogg");
		}
		if (glfwGetKey(Window, scheme.Backward) == GLFW_PRESS) {
			this->move(vec3(-moveStep, 0.f, 0.f));
            shouldMove = true;
		}
		if (glfwGetKey(Window, scheme.Forward) == GLFW_PRESS) {
			this->move(vec3(moveStep, 0.f, 0.f));
            shouldMove = true;
		}
        if (glfwGetKey(Window, scheme.Left) == GLFW_PRESS) {
            if (this->position.z >= 0)
                this->move(vec3(0.f, 0.f, -1.f));
        }
        if (glfwGetKey(Window, scheme.Right) == GLFW_PRESS) {
            if (this->position.z <= -1)
                this->move(vec3(0.f, 0.f, 1.f));
        }

        isMoving = shouldMove;
	}

    void printState() {
        //system("cls");
        cout << string(10, '*') << endl;
        cout << "Hero State:\n"
            << "Lives: " << lives << endl
            << "Coins: " << coins << endl;

        cout << "Game State: ";
        (lives <= 0) ? cout << "Game Over\n" : cout << "Game Running\n";
        cout << string(10, '*') << endl;
    }

    void setControls(bool isFlipped) {
        if (isFlipped) {
            this->scheme = HeroFlippedControl;
        } else {
            this->scheme = HeroNormalControl;
        }
    }
	~Hero();
};
