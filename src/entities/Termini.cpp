#include "entities/Termini.hpp"

Termini::Termini(unsigned int WIDTH,
				 unsigned int HEIGHT,
				 unsigned int FSIZE,
				 const char* fontPath):
width(WIDTH),
height(HEIGHT),
fsize(FSIZE)
{
	if (FT_Init_FreeType(&lib))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (FT_New_Face(lib, fontPath, 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		exit(EXIT_FAILURE);
	}

	FT_Set_Pixel_Sizes(face, 0, fsize);
	if (loadGlyphsTexture())
	{
		exit(EXIT_FAILURE);
	}

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6*4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Termini::~Termini()
{
	FT_Done_Face(face);
	FT_Done_FreeType(lib);
}

void Termini::Render()
{
	Shader::setMat4(shader, "projection", &projMatrix);

	renderText("Hello world", 20, 20, glm::vec3(1.0, 1.0, 0.0));
}

int Termini::loadGlyphsTexture()
{
	unsigned int texture;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (unsigned char c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph > " << (int)c << std::endl;
			return 1;
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 GL_RED,
					 face->glyph->bitmap.width,
					 face->glyph->bitmap.rows,
					 0,
					 GL_RED,
					 GL_UNSIGNED_BYTE,
					 face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		Character character = {texture,
							   face->glyph->advance.x,
							   glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
							   glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top)};

		characters.insert(std::pair<char, Character>(c, character));
	}
	
	return 0;
}

void Termini::renderText(std::string text, float x, float y, glm::vec3 color)
{
	Character ch;

	glUseProgram(shader);
	Shader::setVec3(shader, "textColor", &color);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	std::string::const_iterator c;

	for (c = text.begin(); c != text.end(); c++)
	{
		ch = characters[*c];

		float xpos = x + ch.Bearing.x;
		float ypos = y - (ch.GlyphSize.y - ch.Bearing.y);

		float w = ch.GlyphSize.x;
		float h = ch.GlyphSize.y;

		float vertices[6][4] = {{xpos, 		ypos + h, 	0.0f, 0.0f},
								{xpos, 		ypos,	 	0.0f, 1.0f},
								{xpos + w, 	ypos,	 	1.0f, 1.0f},

								{xpos, 		ypos + h, 	0.0f, 0.0f},
								{xpos + w, 	ypos,	 	1.0f, 1.0f},
								{xpos + w,	ypos + h, 	1.0f, 0.0f}};

		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.Advance >> 6);
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}