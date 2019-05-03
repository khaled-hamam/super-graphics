#pragma once
#include <gl/glew.h>
#include "directions.h"

struct CollisionResult {
    bool areColliding;
    Directions direction;
    GLfloat distance;
};