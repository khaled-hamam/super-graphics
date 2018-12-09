#pragma once
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
using namespace std;

class SuperGraphicsEngine
{
private:
    GLFWwindow* window;
    GLuint windowWidth;
    GLuint windowHeight;
    GLuint programID;
    FPCamera mainCamera;

    void initialize();
    void initializeGLFW();
    void initializeGLEW();
    void initializeGLOptions();
    void render();
    void handleInput();

public:
    SuperGraphicsEngine();
    void start();
};
