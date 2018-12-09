#pragma once    
#include "Model.h"
#include "Primitives.h"

class Cat : public Model {
public:
    Cat() {
        primitives = {
          new Quad(ResourceManager::getTexture("cat"), vec3(0.f, 1.f, 0.f), vec3(0.f), vec3(0.3f)),

          new Cube(ResourceManager::getTexture("box"), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f)),

          new Cube(ResourceManager::getTexture("box"), vec3(-0.5f, 0.f, -5.f), vec3(0.f, 0.f, 0.f), vec3(1.f)),

          new Cube(ResourceManager::getTexture("box"), vec3(-0.5f, 1.f, -5.f), vec3(0.f, 0.f, 0.f), vec3(1.f)),

          new Cube(ResourceManager::getTexture("box"), vec3(2.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(1.f)),

          // new Quad(ResourceManager::getTexture("bricks"), vec3(0.f, -0.5f, 0.f), vec3(90.f, 0.f, 0.f), vec3(50.f, 1.f, 50.f))
        };
    }

    void update() {
        primitives[0]->rotation += vec3(0.f, 1.f, 0.f);
    }
};