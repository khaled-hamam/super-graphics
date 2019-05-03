#pragma once
#include <gl/glew.h>
#include <vector>
#include "ResourceManager.h"
#include "texture.h"

class Skybox {
private:
    GLuint vertexArrayID;
    GLuint vertexBufferID;
    GLuint indicesArrayBuffer;

    bool nightMode;

    void init() {
        GLfloat SIZE = 500.0f;
        std::vector<GLfloat> vertices
        {
            //Back
             SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE, -SIZE,
            -SIZE,  SIZE, -SIZE,
             SIZE,  SIZE, -SIZE,

            //Front
            -SIZE, -SIZE, SIZE,
             SIZE, -SIZE, SIZE,
             SIZE,  SIZE, SIZE,
            -SIZE,  SIZE, SIZE,

            //Right
            SIZE, -SIZE,  SIZE,
            SIZE, -SIZE, -SIZE,
            SIZE,  SIZE, -SIZE,
            SIZE,  SIZE,  SIZE,

            //Left
            -SIZE, -SIZE, -SIZE,
            -SIZE, -SIZE,  SIZE,
            -SIZE,  SIZE,  SIZE,
            -SIZE,  SIZE, -SIZE,

            //Top
            -SIZE, SIZE,  SIZE,
             SIZE, SIZE,  SIZE,
             SIZE, SIZE, -SIZE,
            -SIZE, SIZE, -SIZE,

            //Bottom
            -SIZE, -SIZE, -SIZE,
             SIZE, -SIZE, -SIZE,
             SIZE, -SIZE,  SIZE,
            -SIZE, -SIZE,  SIZE,
        };

        std::vector<GLuint> indices
        {
            0, 1, 2,
            2, 3, 0,

            4, 5, 6,
            6, 7, 4,

            8, 9, 10,
            10, 11, 8,

            12, 13, 14,
            14, 15, 12,

            16, 17, 18,
            18, 19, 16,

            20, 21, 22,
            22, 23, 20
        };

        glGenVertexArrays(1, &vertexArrayID);
        glBindVertexArray(vertexArrayID);

        glGenBuffers(1, &vertexBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof GLfloat, vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &indicesArrayBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesArrayBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof GLuint, indices.data(), GL_STATIC_DRAW);

	    glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindVertexArray(0);
    }

public:
    Skybox() {
        this->nightMode = false;
        init();
    }

    void setNightMode() {
        this->nightMode = true;
    }
    
    void setDayMode() {
        this->nightMode = false;
    }

    void render() {
        glBindVertexArray(vertexArrayID);

        GLint OldCullFaceMode;
        glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
        GLint OldDepthFuncMode;
        glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);
        glCullFace(GL_FRONT);
        glDepthFunc(GL_LEQUAL);

        ResourceManager::getShader("skyboxShader")->useShader();
        Texture *texture = this->nightMode 
            ? ResourceManager::getTexture("skybox-night")
            : ResourceManager::getTexture("skybox-day");

        texture->Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        texture->UnBind();

        glCullFace(OldCullFaceMode); 
        glDepthFunc(OldDepthFuncMode);

        glBindVertexArray(0);
    }
};