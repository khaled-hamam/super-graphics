#include "Model.h"

Model::Model()
{
}

void Model::render()
{
    for (auto &primitive : primitives) {
        primitive->render();
    }
}

Model::~Model()
{
    for (Primitive* &primitive : primitives) {
        delete primitive;
    }
}