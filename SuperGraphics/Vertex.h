#pragma once
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textCoord;
    glm::vec3 normal = glm::vec3(0.f, 0.f, 1.f);
};