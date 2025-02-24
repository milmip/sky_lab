#include "entities/Object.hpp"

Object::~Object()
{
	delete[] textures;
}

void Object::Init(unsigned int SHADERR, unsigned int NBR_TEXT, const char** TEXTURES_LOCATION)
{
	shader = SHADERR;
	nbrText = NBR_TEXT;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, getVertexDataSize(), getVertexData(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, getIndicesDataSize(), getIndicesData(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Texture
	stbi_set_flip_vertically_on_load(true);

	glUseProgram(shader);
	textures = new unsigned int[nbrText];

	for (int i = 0; i < nbrText; ++i)
	{
		glGenTextures(1, textures + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		
		unsigned char *data = stbi_load(TEXTURES_LOCATION[i], &width, &height, &nrChannels, 0);
		//unsigned char *data = stbi_load(TEXTURES_LOCATION[i], &width, &height, &nrChannels, 0);
		if (data)
		{
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		    glGenerateMipmap(GL_TEXTURE_2D);
		    std::cout << "Texture loaded > " << TEXTURES_LOCATION[i] << std::endl;
		}
		else
		{
		    std::cout << "Failed to load texture > " << std::endl;
		}
		stbi_image_free(data);
		
		const char uni_name[] = {'t', 'e', 'x', 't', 'u', 'r', 'e', (char)(i + 49)};
		Shader::setInt(shader, uni_name, i);
	}
	/*Shader::setInt(shader, "texture1", 0);
	Shader*/

	//dans l'ordre
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::Bind()
{
	for (int i = 0; i < nbrText; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}

	glUseProgram(shader);
	glBindVertexArray(vao);
}

void Object::Draw()
{
	glDrawElements(GL_TRIANGLES, getIndicesDataSize(), GL_UNSIGNED_INT, 0);
}

void Object::UpdateModelMatrix()
{
	model[3][0] = position[0];
	model[3][1] = position[1];
	model[3][2] = position[2];
}