#pragma once
#include <gl/glew.h>
#include <glm/gtx/transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "Vertex.h"
#include "texture.h"
#include "shader.hpp"
#include "ResourceManager.h"
using namespace std;
using namespace glm;

class Primitive
{
protected:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;

    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint indicesBufferID;

    vec3 origin;

    Texture *texture;

public:
    vec3 scale;
	vec3 position;
    vec3 rotation;
    Primitive(Texture *texture, vec3 position, vec3 rotation, vec3 scale);
    void init();
    void render();
    void render(Texture *texture);
    mat4 getModelMatrix();
    ~Primitive();
};

