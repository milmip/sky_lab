#include "entities/object.hpp"

Object::Object(){}

Object::~Object()
{
	delete[] textures;
}

void Object::init(unsigned int SHAER, unsigned int NBR_TEXT, const char** textures_location)
{
	shader = SHAER;
	nbr_text = NBR_TEXT;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, get_vertex_data_size(), get_vertex_data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_indices_data_size(), get_indices_data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Texture
	stbi_set_flip_vertically_on_load(true);

	glUseProgram(shader);
	textures = new unsigned int[nbr_text];

	for (int i = 0; i < nbr_text; ++i)
	{
		glGenTextures(1, textures + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		
		unsigned char *data = stbi_load(textures_location[i], &width, &height, &nrChannels, 0);
		//unsigned char *data = stbi_load(textures_location[i], &width, &height, &nrChannels, 0);
		if (data)
		{
		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		    glGenerateMipmap(GL_TEXTURE_2D);
		    std::cout << "Texture loaded > " << textures_location[i] << std::endl;
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

void Object::bind()
{
	//int i = (std::rand()) % 2;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	/*for (int i = 0; i < nbr_text; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}*/

	glUseProgram(shader);
	glBindVertexArray(vao);
}

void Object::draw()
{
	glDrawElements(GL_TRIANGLES, get_indices_data_size(), GL_UNSIGNED_INT, 0);
}

void Object::update_model_matrix()
{
	//rotation
	/*glm::mat4 x_rot = glm::mat4(1.0f);
	x_rot[1][1] = cos(direction[0]);
	x_rot[1][2] = sin(direction[0]);
	x_rot[2][1] = -sin(direction[0]);
	x_rot[2][2] = cos(direction[0]);
	//printmat4(&x_rot);

	glm::mat4 y_rot = glm::mat4(1.0f);
	y_rot[0][0] = cos(direction[1]);
	y_rot[2][0] = sin(direction[1]);
	y_rot[0][2] = -sin(direction[1]);
	y_rot[2][2] = cos(direction[1]);
	//printmat4(&y_rot);

	glm::mat4 z_rot = glm::mat4(1.0f);
	z_rot[0][0] = cos(direction[2]);
	z_rot[0][1] = sin(direction[2]);
	z_rot[1][0] = -sin(direction[2]);
	z_rot[1][1] = cos(direction[2]);
	//printmat4(&z_rot);

	
	model = x_rot * y_rot * z_rot;*/
	//printmat4(&model);
	//translation
	//pos[0] += 0.0005;
	model[3][0] = pos[0];
	model[3][1] = pos[1];
	model[3][2] = pos[2];
}

