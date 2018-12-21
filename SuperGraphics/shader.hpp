#pragma once
#include "libs.h"
using namespace std;

class Shader {
private:
    GLuint shaderID;
    GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);

public:
    Shader() {}
    Shader(const char *vertex_file_path, const char *fragment_file_path);
    void useShader();
    void setMat4(string matrix, const GLfloat *value);
    void setVec3(string vecName, const GLfloat *value);
    void setFloat(string floatName, const GLfloat *value);
};
