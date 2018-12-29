#include "ResourceManager.h"

unordered_map<string, Shader*> ResourceManager::shaders;
unordered_map<string, Texture*> ResourceManager::textures;
unordered_map<string, ISoundEngine*> ResourceManager::soundEngines;

void ResourceManager::initializeShaders()
{
	shaders["programShader"] = new Shader("shaders/VertexShader.vertexshader", "shaders/FragmentShader.fragmentshader");
	shaders["cubemapShader"] = new Shader("shaders/cubemap.vertexshader", "shaders/cubemap.fragmentshader");
    shaders["skyboxShader"] = new Shader("shaders/skybox.vertexshader", "shaders/skybox.fragmentshader");
	shaders["textShader"] = new Shader("shaders/text.vertexshader", "shaders/text.fragmentshader");
}

void ResourceManager::initializeTextures()
{
	textures["hero"] = new Texture("Assets/alien/alien_front.png",0);

    textures["alien_idle_1"] = new Texture("Assets/alien/alien_idle_1.png", 0);
    textures["alien_idle_2"] = new Texture("Assets/alien/alien_idle_2.png", 0);
    textures["alien_idle_3"] = new Texture("Assets/alien/alien_idle_3.png", 0);
    textures["alien_run_1"] = new Texture("Assets/alien/alien_run_1.png", 0);
    textures["alien_run_2"] = new Texture("Assets/alien/alien_run_2.png", 0);
    textures["alien_run_3"] = new Texture("Assets/alien/alien_run_3.png", 0);
    textures["alien_run_4"] = new Texture("Assets/alien/alien_run_4.png", 0);
    textures["alien_run_5"] = new Texture("Assets/alien/alien_run_5.png", 0);
    textures["alien_run_6"] = new Texture("Assets/alien/alien_run_6.png", 0);

    textures["cat"] = new Texture("Assets/cat.png", 0);
	textures["coin"] = new Texture("Assets/coin.png", 0);
	textures["spaceship"] = new Texture("Assets/spaceship.png", 0);
    textures["box"] = new Texture("Assets/box/box.jpg", 0);
	textures["box1"] = new Texture("Assets/box/box2.jpg", 0);
	textures["brownBlock"] = new Texture("Assets/box/brownBlock.jpg", 0);
    textures["lava"] = new Texture("Assets/lava.jpg", 0);
    textures["portal"] = new Texture("Assets/portal.jpg", 0);

    textures["villain01"] = new Texture("Assets/villain/villain01.png", 0);
    textures["villain02"] = new Texture("Assets/villain/villain02.png", 0);
    textures["villain-gold01"] = new Texture("Assets/villain/villain-gold01.png", 0);
    textures["villain-gold02"] = new Texture("Assets/villain/villain-gold02.png", 0);

    textures["skybox-day"] = new Texture(vector<string> {
        "Assets/skybox/skybox_right.jpg",
        "Assets/skybox/skybox_left.jpg",
        "Assets/skybox/skybox_up.jpg",
        "Assets/skybox/skybox_down.jpg",
        "Assets/skybox/skybox_back.jpg",
        "Assets/skybox/skybox_front.jpg"
	}, 0);

    textures["skybox-night"] = new Texture(vector<string> {
        "Assets/skybox-night/skybox_right.jpg",
        "Assets/skybox-night/skybox_left.jpg",
        "Assets/skybox-night/skybox_up.jpg",
        "Assets/skybox-night/skybox_down.jpg",
        "Assets/skybox-night/skybox_back.jpg",
        "Assets/skybox-night/skybox_front.jpg"
	}, 0);
}

void ResourceManager::initializeSoundEngines()
{
	ResourceManager::soundEngines["backgroundEngine"] = createIrrKlangDevice();
	ResourceManager::soundEngines["effectsEngine"] = createIrrKlangDevice();

	// Initialize Sound Options
	ResourceManager::soundEngines["backgroundEngine"]->setSoundVolume(0.3f);
	ResourceManager::soundEngines["effectsEngine"]->setSoundVolume(1.f);
}

void ResourceManager::initializeResources()
{
    initializeShaders();
    initializeTextures();
	initializeSoundEngines();
}

Shader * ResourceManager::getShader(string shaderName)
{
    return shaders[shaderName];
}

Texture * ResourceManager::getTexture(string textureName)
{
    return ResourceManager::textures[textureName];
}

ISoundEngine * ResourceManager::getSoundEngine(string engineName)
{
	return ResourceManager::soundEngines[engineName];
}

void ResourceManager::bindCamera(FPCamera * activeCamera)
{
    activeCamera->updatePositionToHero();

    for (auto &shader : shaders) {
        shader.second->setMat4("ProjectionMatrix", &activeCamera->GetProjectionMatrix()[0][0]);
        shader.second->setMat4("ViewMatrix", &activeCamera->GetViewMatrix()[0][0]);

        shader.second->setVec3("cameraPos", &activeCamera->getPosition()[0]);
        shader.second->setVec3("lightPos", &activeCamera->getPosition()[0]);
    }
}

Shader * ResourceManager::getAppropriateShader(Texture * texture)
{
    if (texture && texture->textureType == GL_TEXTURE_CUBE_MAP) {
        return ResourceManager::getShader("cubemapShader");
    } else {
        return ResourceManager::getShader("programShader");
    }
}

void ResourceManager::playSoundEffect(char* audioName)
{
	bool isPlaying = ResourceManager::getSoundEngine("effectsEngine")->isCurrentlyPlaying(audioName);
	if (isPlaying == false) {
		ResourceManager::getSoundEngine("effectsEngine")->play2D(audioName, GL_FALSE);
	}
}

void ResourceManager::playBackgroundMusic()
{
	ResourceManager::getSoundEngine("backgroundEngine")->play2D("Audio/getout.ogg", GL_TRUE);
}

ResourceManager::~ResourceManager()
{
    for (auto &shader : shaders) {
        delete shader.second;
    }
    for (auto &texture : textures) {
        delete texture.second;
    }
}
