#ifndef OBJECT
#define OBJECT

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "graphics/stb_image.h"
#include "graphics/Shader.hpp"

#include <iostream>

void printmat4(glm::mat4* mat);

class Object
{
public:
	Object() = default;
	virtual ~Object();

	void Init(unsigned int SHADERR, unsigned int NBR_TEXT, const char** TEXTURES_LOCATION);

	int GetShader(){return shader;}
	glm::mat4* GetModelMatrix(){return &model;}

	void Bind();
	void Draw();

	void UpdateModelMatrix();

private:
	unsigned int vao, vbo, ebo, shader, nbrText;
	unsigned int* textures = NULL;
	
	glm::vec3 direction = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);

	glm::mat4 model = glm::mat4(1.0f);

	virtual float* getVertexData() = 0;
	virtual int getVertexDataSize() = 0;

	virtual unsigned int* getIndicesData() = 0;
	virtual int getIndicesDataSize() = 0;

	virtual int* getAttribPtr() = 0;
	virtual int getNPtr() = 0;
	virtual int getAttribSize() = 0;
};

#endif