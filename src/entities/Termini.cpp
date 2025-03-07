#include "entities/Termini.hpp"

void Termini::Init(unsigned int SHAD, const char* font_path,
				   unsigned int WIDTH, unsigned int HEIGHT,
				   unsigned int COL, unsigned int ROW)
{
	scr_width = WIDTH;
	scr_height = HEIGHT;
	col = COL;
	row = ROW;

	scale = 0.5f;

	shader = SHAD;

	int bearingMaxUp = 0;
	int bearingMaxDown = 0;

	backgroundShader.Init("shaders/terminiGroundVert.glsl", "shaders/terminiGroundFrag.glsl");
	background.Init(backgroundShader.ID, 0, NULL);

	glyphProjMatrix = glm::ortho(0.0f, static_cast<float>(scr_width), static_cast<float>(scr_height), 0.0f);

	glUseProgram(shader);
	Shader::setMat4(shader, "projection", &glyphProjMatrix);

	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

	FT_Face face;
	if (FT_New_Face(ft, font_path, 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}
	else
	{
		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}

			unsigned int texture;
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
								   glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
								   glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
								   static_cast<unsigned int>(face->glyph->advance.x)};
			characters.insert(std::pair<char, Character>(c, character));

			if (face->glyph->bitmap_top > bearingMaxUp)
			{
				bearingMaxUp = face->glyph->bitmap_top;
			}
			int dif = static_cast<int>(face->glyph->bitmap.rows) - static_cast<int>(face->glyph->bitmap_top);
			if (dif > bearingMaxDown)
			{
				bearingMaxDown = dif;
			}
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	tileH = static_cast<unsigned int>(bearingMaxUp + bearingMaxDown);
	tileW = static_cast<unsigned int>((characters['a'].Advance >> 6));

	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Termini::Draw()
{
	renderText(preprompt, 0.0f, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	renderText(prompt, tileW * scale, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	renderText(cursor, (prompt.size() + preprompt.size()) * tileW * scale, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	updateBackgroundMatrix(col * tileW * scale, row * tileH * scale);
	backgroundShader.Use();
	Shader::setMat3(backgroundShader.ID, "upInTheCorner", &upInTheCorner);
	background.Bind();
	background.Draw();
}

void Termini::ProcessInput(InputManager* input)
{
	unsigned int vc = input->GetVisibleChar();
	unsigned int ivc = input->GetInvisibleChar();
	if (vc && (preprompt.size() + prompt.size() + cursor.size()) < col)
	{
		prompt.append(1, static_cast<char>(vc));
	}
	if (ivc)
	{
		if (ivc == UTF_SUPP)
		{
			if (!prompt.empty())
			{
				prompt.erase(prompt.size() - 1, 1);
			}
		}
	}


}

void Termini::renderText(std::string text, float x, float y, glm::vec3 color)
{
	glUseProgram(shader);
	Shader::setVec3(shader, "textColor", &color);
	y += tileH * scale;

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);

	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++) 
	{
		Character ch = characters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y + (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		float vertices[6][4] = {{ xpos,     ypos - h,   0.0f, 0.0f },
								{ xpos,     ypos,       0.0f, 1.0f },
								{ xpos + w, ypos,       1.0f, 1.0f },

								{ xpos,     ypos - h,   0.0f, 0.0f },
								{ xpos + w, ypos,       1.0f, 1.0f },
								{ xpos + w, ypos - h,   1.0f, 0.0f }};
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (ch.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Termini::updateBackgroundMatrix(unsigned int wPx, unsigned int hPx)
{
	float k = static_cast<float>(wPx) / static_cast<float>(scr_width);
	float m = static_cast<float>(hPx) / static_cast<float>(scr_height);
	upInTheCorner = glm::mat3(k,    0.0f, 0.0f,
							  0.0f, m,    0.0f,
							  k-1.0f, 1.0f-m, 1.0f);
}