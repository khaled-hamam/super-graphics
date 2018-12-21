#pragma once
#include <map>
#include "texture.h"
#include "ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

struct Character {
	GLuint textureID;
	glm::vec2 size;
	glm::vec2 bearing;
	GLuint nextGlyph;
};

class TextRenderer
{
	map<GLchar, Character> characters;
	Shader *textShader;
	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint indicesBufferID;

public:
	TextRenderer(int ,int);
	void loadFont(string ,int);
	void renderText(string, float, float, float, glm::vec3);
	~TextRenderer();
};

