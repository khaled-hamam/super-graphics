#pragma once
#include <irrKlang/irrKlang.h>
#include <vector>
#include "Primitives.h"
#include "ResourceManager.h"
#include "directions.h"
using namespace std;
using namespace irrklang;

class Model
{
protected:
    vector<Primitive*> primitives;
	
public:
	vec3 position;
	vec3 scale;
	vec3 rotation;
    bool destroyed = false;

    Model();
    ~Model();
    virtual void render();
	void move(vec3 position);
	void rotate(vec3 rotation);
	void changeScale(vec3 scale);
    virtual void collision(Model *hero, Directions direction, GLfloat distance);
    virtual void update() = 0;
};

