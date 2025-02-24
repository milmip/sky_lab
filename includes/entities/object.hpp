#ifndef OBJECT
#define OBJECT

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "graphics/stb_image.h"
#include "graphics/shader.hpp"

#include <iostream>
#include <bits/stdc++.h>

void printmat4(glm::mat4* mat);

class Object
{
public:
	Object();
	virtual ~Object();

	void init(unsigned int SHAER, unsigned int NBR_TEXT, const char** textures_location);

	int get_shader(){return shader;}
	glm::mat4* get_model_matrix(){return &model;}

	void bind();
	void draw();

	void update_model_matrix();

private:
	unsigned int vao, vbo, ebo, shader, nbr_text, texture;
	unsigned int* textures = NULL;
	
	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 pos = glm::vec3(0.0, 0.0, 0.0);

	glm::mat4 model = glm::mat4(1.0f);

	virtual float* get_vertex_data() = 0;
	virtual int get_vertex_data_size() = 0;

	virtual unsigned int* get_indices_data() = 0;
	virtual int get_indices_data_size() = 0;

};




#endif