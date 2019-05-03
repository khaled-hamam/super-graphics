#include "Light.h"

GLuint Light::directionalLightsCount = 0;
GLuint Light::pointLightsCount = 0;
GLuint Light::spotLightsCount = 0;

void Light::setCountUniforms()
{
    Shader *shader = ResourceManager::getShader("programShader");
    shader->setInteger("directionalLightsCount", directionalLightsCount);
    shader->setInteger("pointLightsCount", pointLightsCount);
    shader->setInteger("spotLightsCount", spotLightsCount);
}

Light::Light(LightType light, vec3 ambient, vec3 diffuse, vec3 specular)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;

    switch(light) {
    case DIRECTIONAL:
        this->lightName = "directionalLights[" + to_string(directionalLightsCount) + "]";
        directionalLightsCount++;
        break;
    case POINT:
        this->lightName = "pointLights[" + to_string(pointLightsCount) + "]";
        pointLightsCount++;
        break;
    case SPOT:
        this->lightName = "spotLights[" + to_string(spotLightsCount) + "]";
        spotLightsCount++;
    }

    setCountUniforms();
}

void Light::clearLights()
{
    Light::spotLightsCount = 0;
    Light::directionalLightsCount = 0;
    Light::pointLightsCount = 0;
    setCountUniforms();
}

void Light::use()
{
    Shader *shader = ResourceManager::getShader("programShader");
    shader->setVec3(lightName + ".ambient", &ambient[0]);
    shader->setVec3(lightName + ".diffuse", &diffuse[0]);
    shader->setVec3(lightName + ".specular", &specular[0]);
}


Light::~Light()
{
}
