#pragma once
#include "libs.h"

class Texture
{

public:
	int width, height;
	int numComponents;
    GLenum textureType;
	unsigned char * data;
	int texUnit;
	void Bind();
    void UnBind();
    void load2DTexture(const std::string &fileName, int texUnit);
    void loadCubeMapTexture(std::vector<std::string> files, int texUnit);
	Texture(const std::string& fileName, int texUnit);
    Texture(const std::vector<std::string> fileName, int texUnit);
	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}
	GLuint m_texture;
};
