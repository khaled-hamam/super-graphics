#include "texture.h"
#include "stb_image.h"
#include <iostream>
using namespace std;

Texture::Texture(const std::string& fileName, int texUnit_)
{
    this->textureType = GL_TEXTURE_2D;
    this->load2DTexture(fileName, texUnit_);
}

Texture::Texture(std::vector<std::string> files, int texUnit)
{
    this->textureType = GL_TEXTURE_CUBE_MAP;
    this->loadCubeMapTexture(files, texUnit);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
	glActiveTexture(texUnit);
	glBindTexture(textureType, m_texture);
}

void Texture::UnBind()
{
    glActiveTexture(0);
	glBindTexture(textureType, 0);
}

void Texture::load2DTexture(const std::string & fileName, int texUnit_)
{
    texUnit = texUnit_;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, STBI_rgb_alpha);
    if(data == NULL)
		cout<< "Unable to load texture: " << fileName << endl;

	glActiveTexture(texUnit);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0); 

    stbi_image_free(data);
}

void Texture::loadCubeMapTexture(std::vector<std::string> files, int texUnit_)
{
    texUnit = texUnit_;
	glActiveTexture(texUnit);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

    unsigned char* data;
    for (int i = 0; i < files.size(); ++i) {
        string fileName = files[i];
        data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 0);
        if(data == NULL)
		    cout<< "Unable to load texture: " << fileName << endl;

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE); 

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); 
}
