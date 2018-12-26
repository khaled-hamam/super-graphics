#pragma once
#include "libs.h"
#include "shader.hpp"
#include "texture.h"
#include "FPCamera.h"
#include <irrKlang/irrKlang.h>
using namespace irrklang;

static class ResourceManager {
private:
    static unordered_map<string, Shader*> shaders;
	static unordered_map<string, Texture*> textures;
	static unordered_map<string, ISoundEngine*> soundEngines;

    static void initializeShaders();
    static void initializeTextures();
	static void initializeSoundEngines();

public:
    static void initializeResources();
    static Shader* getShader(string shaderName);
    static Texture* getTexture(string textureName);
    static void bindCamera(FPCamera *activeCamera);
	static ISoundEngine* getSoundEngine(string engineName);
    static Shader* getAppropriateShader(Texture *texture);
	static void playSoundEffect(char *);
	static void playBackgroundMusic();
    ~ResourceManager();
};