#pragma once
#include <irrKlang/irrKlang.h>
#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <iostream>
#include "shader.hpp"
#include "FPCamera.h"
#include "colors.h"
#include "texture.h"
#include "Skybox.h"
#include "LevelGenerator.h"
#include "CollisionResult.h"
using namespace irrklang;
using namespace std;


class SuperGraphicsEngine
{
private:
    GLFWwindow* window;
    GLuint windowWidth;
    GLuint windowHeight;
    GLuint programID;
    FPCamera mainCamera;

    Hero *hero;
    vector<Model*> level;

    void initialize();
    void initializeGLFW();
    void initializeGLEW();
    void initializeGLOptions();
    void render();
    void handleInput();
    void checkCollision();
	CollisionResult areColliding(Hero *hero, Model *model);

public:
    SuperGraphicsEngine();
    void start();
};
