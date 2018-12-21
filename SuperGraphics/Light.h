#pragma once
#include <gl/glew.h>
#include <glm/glm.hpp>
#include "ResourceManager.h"
using namespace glm;

enum LightType {
    DIRECTIONAL,
    POINT,
    SPOT
};

class Light {
    static GLuint directionalLightsCount;
    static GLuint pointLightsCount;
    static GLuint spotLightsCount;

public:
    string lightName;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    Light(LightType light, vec3 ambient, vec3 diffuse, vec3 specular);
    virtual void use();
    ~Light();
};

