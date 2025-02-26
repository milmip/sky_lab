#ifndef TERMINI
#define TERMINI

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "graphics/Shader.hpp"

#include <iostream>
#include <string>
#include <map>

struct Character
{
	unsigned int TextureID;
	unsigned int Advance;

	glm::ivec2 GlyphSize;
	glm::ivec2 Bearing;
};

class Termini
{
public:
	Termini(unsigned int WIDTH,
			unsigned int HEIGHT,
			unsigned int FSIZE,
			const char* fontPath);
	~Termini();

	void Render();

	void SetShader(unsigned int id){shader = id;}
	void SetProjM(glm::mat4 proj){projMatrix = proj;}

private:
	unsigned int vao, vbo, shader;
	unsigned int width, height, fsize;

	std::map<char, Character> characters;

	glm::mat4 projMatrix;

	FT_Library lib;
	FT_Face face;

	int loadGlyphsTexture();
	void renderText(std::string text, float x, float y, glm::vec3 color);
};

#endif