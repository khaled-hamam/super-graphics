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
#include "TextRenderer.h"
#include "GameState.h"
using namespace irrklang;
using namespace std;


class SuperGraphicsEngine
{
private:
    GLFWwindow* window;
    GLuint windowWidth;
    GLuint windowHeight;
    
    GameState gameState = READY;
	TextRenderer *textEngine;
    FPCamera mainCamera;
    GLfloat drawDistance = 25.f;
    Level *level;

    void initialize();
    void initializeGLFW();
    void initializeGLEW();
    void initializeGLOptions();
    void render();
    void renderReadyScreen();
    void renderRunningScreen();
    void renderGameOverScreen();
    void handleInput();
    void checkCollision();
	CollisionResult areColliding(Hero *hero, Model *model);

public:
    SuperGraphicsEngine();
    void start();
};
