#include "Primitive.h"

Primitive::Primitive(Texture *texture, vec3 position, vec3 rotation, vec3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
    this->texture = texture;
}

void Primitive::init()
{
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof Vertex, vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &indicesBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof GLuint, indices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));

    
	glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));

    
	glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textCoord));

    glBindVertexArray(0);
}

void Primitive::render()
{
    glBindVertexArray(vertexArrayID);

    Shader *shader = ResourceManager::getAppropriateShader(texture);
    shader->useShader();
    shader->setMat4("ModelMatrix", &getModelMatrix()[0][0]);

    if (texture) {
        texture->Bind();
    }
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    if (texture) {
        texture->UnBind();
    }
}

mat4 Primitive::getModelMatrix()
{
    mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scale);
    modelMatrix = glm::rotate(modelMatrix, rotation.x, vec3(1.f, 0.f, 0.f));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, vec3(0.f, 1.f, 0.f));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, vec3(0.f, 0.f, 1.f));
    return modelMatrix;
}


Primitive::~Primitive()
{
    glDeleteVertexArrays(1, &vertexArrayID);
	glDeleteBuffers(1, &vertexBufferID);
    glDeleteBuffers(1, &indicesBufferID);
    delete texture;
}
