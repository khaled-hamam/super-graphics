#pragma once
#include "libs.h"
#include "shader.hpp"
#include "texture.h"
#include "FPCamera.h"

static class ResourceManager {
private:
    static unordered_map<string, Shader*> shaders;
    static unordered_map<string, Texture*> textures;

    static void initializeShaders();
    static void initializeTextures();

public:
    static void initializeResources();
    static Shader* getShader(string shaderName);
    static Texture* getTexture(string textureName);
    static void bindCamera(FPCamera *activeCamera, glm::vec3 heroPositon);
    static Shader* getAppropriateShader(Texture *texture);
    ~ResourceManager();
};