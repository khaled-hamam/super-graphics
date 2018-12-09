#pragma once
#include <vector>
#include "Primitives.h"
#include "ResourceManager.h"
using namespace std;

class Model
{
protected:
    vector<Primitive*> primitives;

public:
    Model();
    ~Model();
    void render();
    virtual void update() = 0;
};

