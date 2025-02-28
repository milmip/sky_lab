#ifndef TERMINI
#define TERMINI

#include <glad/glad.h>
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "graphics/Shader.hpp"
#include "entities/Mesh.hpp"
#include "core/InputManager.hpp"

#include <iostream>
#include <map>
#include <string>

struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Termini
{
public:
	Termini() = default;
	~Termini() = default;

	void Init(unsigned int shad, const char* font_path, unsigned int width, unsigned int height);
	void Draw();
	void ProcessInput(const InputManager* input);

private:
	unsigned int vao, vbo, shader, scr_width, scr_height;
	std::map<GLchar, Character> characters;

	glm::mat4 glyphProjMatrix;

	glm::mat3 upInTheCorner;
	Shader backgroundShader;
	Square background;

	void renderText(std::string text, float x, float y, float scale, glm::vec3 color);	
	void updateBackgroundMatrix(unsigned int wPx, unsigned int hPx);
};
#endif