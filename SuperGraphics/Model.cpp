#include "Model.h"

Model::Model()
{
    scale = vec3(1.f);
}

void Model::render()
{
    for (auto &primitive : primitives) {
        primitive->render();
    }
}
void Model::move(vec3 position)
{
	for (auto &primitive : primitives) {
		primitive->position += position;
	}
	this->position += position;
}
void Model::rotate(vec3 rotation) {

	for (auto &primitive : primitives) {
		primitive->rotation += rotation;
	}
	this->rotation += rotation;
}
void Model::changeScale(vec3 scale) {
	for (auto &primitive : primitives) {
		primitive->scale *= scale;
	}
	this->scale *= scale;
}
void Model::collision(Hero & hero)
{
}
Model::~Model()
{
    for (Primitive* &primitive : primitives) {
        delete primitive;
    }
}