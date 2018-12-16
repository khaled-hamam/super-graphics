#pragma once
#include <vector>
#include "Primitives.h"
#include "Models.h";
#include "ResourceManager.h"
using namespace std;

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
    virtual void collision(Hero &hero);
    virtual void update() = 0;
};

