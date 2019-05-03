#pragma once
#include <glm/glm.hpp>
#include "Light.h"
#include "Attenuation.h"

class DirectionalLight: public Light {
public:  
    vec3 direction;

    DirectionalLight(
        vec3 direction = vec3(-1.f, -1.f, .5f),
        vec3 ambient =  vec3(0.1f),
        vec3 diffuse =  vec3(0.1f),
        vec3 specular =  vec3(0.1f)
    ) : Light(DIRECTIONAL, ambient, diffuse, specular) {
        this->direction = direction;
    }

    virtual void use() override {
        Light::use();
        Shader *shader = ResourceManager::getShader("programShader");
        shader->setVec3(lightName + ".direction", &direction[0]);
    }
};

class PointLight: public Light {
public:
    vec3 position;
    Attenuation attenuation;

    PointLight(
        vec3 position = vec3(0.f, 1.f, 0.f),
        vec3 ambient =  vec3(1.0f, 1.0f, 1.0f),
        vec3 diffuse =  vec3(0.5f, 0.5f, 0.5f),
        vec3 specular =  vec3(1.0f, 1.0f, 1.0f)
    ) : Light(POINT, ambient, diffuse, specular){
        this->position = position;
        this->attenuation = { 1.0f, 0.09f, 0.032f };
    }

    virtual void use() override {
        Light::use();
        Shader *shader = ResourceManager::getShader("programShader");
        shader->setVec3(lightName + ".position", &position[0]);

        shader->setFloat(lightName + ".constant", &attenuation.constant);
        shader->setFloat(lightName + ".linear", &attenuation.linear);
        shader->setFloat(lightName + ".quadratic", &attenuation.quadratic);
    }
};