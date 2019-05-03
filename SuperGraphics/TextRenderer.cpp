#include "TextRenderer.h"
#include <ft2build.h>
#include FT_FREETYPE_H

TextRenderer::TextRenderer(int width, int height)
{
	textShader = ResourceManager::getShader("textShader");
	textShader->setMat4("projection", &glm::ortho(0.0f, (GLfloat)width, (GLfloat)height, 0.0f)[0][0]);
	textShader->setInteger("text", 0);

	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);

	GLuint indices[]{
		0, 2, 1,
		0, 3, 2
	};

	glGenBuffers(1, &indicesBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::loadFont(string fontName, int fontSize)
{
	this->characters.clear();
	// Then initialize and load the FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) // All functions return a value different than 0 whenever an error occurred
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	// Load font as face
	FT_Face face;
	if (FT_New_Face(ft, fontName.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	// Set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, fontSize);
	// Disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// Then for the first 128 ASCII characters, pre-load/compile their characters and store them
	for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		Character character = {
			texture,
			glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters[c] = character;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// Destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::renderText(string text, float x, float y, float scale, glm::vec3 color)
{
	textShader->useShader();
	textShader->setVec3("textColor", &color[0]);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vertexArrayID);

	for (char c : text) {
		Character currentChar = characters[c];

		float xPosition = x + currentChar.bearing.x * scale;
		float yPosition = y + (characters['H'].bearing.y - currentChar.bearing.y) * scale;
		float width = currentChar.size.x * scale;
		float height = currentChar.size.y *scale;

		GLfloat verts[] = {
			xPosition , yPosition , 
			0.f , 0.f,
			xPosition + width , yPosition ,
			1.f , 0.f,
			xPosition + width , yPosition + height , 
			1.0 , 1.f,
			xPosition , yPosition + height , 
			0.f , 1.f,
		};

		glBindTexture(GL_TEXTURE_2D, currentChar.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (currentChar.nextGlyph >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

TextRenderer::~TextRenderer()
{
}
