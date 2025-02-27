#ifndef MESH
#define MESH

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "entities/Object.hpp"

#include <cmath>

class Sphere : public Object
{
public:
	Sphere(int stacks, int meridans);
	~Sphere();

private:
	int vertexDataSize;
	int indicesDataSize;

	float* vertex;
	unsigned int* indices;

	int attribPtr[3] = {3, 3, 2};
	int nPtr = 3;
	int attribSize = 8;

	float* getVertexData(){return vertex;}
	int getVertexDataSize(){return vertexDataSize;}

	unsigned int* getIndicesData(){return indices;}
	int getIndicesDataSize(){return indicesDataSize;}

	int* getAttribPtr(){return attribPtr;};
	int getNPtr(){return nPtr;};
	int getAttribSize(){return attribSize;};
};


class Square : public Object
{
public:
	Square():
	vertex{ 1.0f,  1.0f,
		   -1.0f,  1.0f,
			1.0f, -1.0f,
		   -1.0f, -1.0f},

	indices{0, 1, 2,
			1, 2, 3}
	{}

private:
	float vertex[8];
	unsigned int indices[6];

	int attribPtr[1] = {2};
	int nPtr = 1;
	int attribSize = 2;

	float* getVertexData(){return vertex;}
	int getVertexDataSize(){return sizeof(vertex);}

	unsigned int* getIndicesData(){return indices;}
	int getIndicesDataSize(){return sizeof(indices);}

	int* getAttribPtr(){return attribPtr;};
	int getNPtr(){return nPtr;};
	int getAttribSize(){return attribSize;};
};

/*class Cube : public Object
{
public:
	Cube():
	vertex{ 0.5f,  0.5f,  0.5f,
		   -0.5f,  0.5f,  0.5f,
			0.5f, -0.5f,  0.5f,
		   -0.5f, -0.5f,  0.5f,

			0.5f,  0.5f, -0.5f,
		   -0.5f,  0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
		   -0.5f, -0.5f, -0.5f},

	indices{0, 1, 4, //orange
			1, 4, 5,

			0, 2, 4, //bleu
			2, 4, 6,

			2, 3, 6, //rouge
			3, 6, 7,

			1, 3, 5, //vert
			3, 5, 7,

			0, 1, 2, //blanc
			1, 2, 3,

			4, 5, 6, //jaune
			5, 6, 7}
	{}

private:
	float vertex[24];
	unsigned int indices[36];

	float* getVertexData(){return vertex;}
	int getVertexDataSize(){return sizeof(vertex);}

	unsigned int* getIndicesData(){return indices;}
	int getIndicesDataSize(){return sizeof(indices);}
};

class Triangle : public Object
{
public:
	Triangle():
	vertex{0.0f, -1.0f, 0.0f,
			0.47f, -0.40f, 0.0f,
			0.88f, 0.24f, 0.0f,

			0.62f, 0.73f, 0.0f,
			0.25f, 0.70f, 0.0f,
			0.0f, 0.26f, 0.0f,

			-0.25f, 0.70f, 0.0f,
			-0.62f, 0.73f, 0.0f,
			-0.88f, 0.24f, 0.0f,

			-0.47f, -0.40f, 0.0f
		},
	indices{0, 1, 5,
			1, 2, 5,
			2, 4, 5,
			2, 3, 4,

			0, 5, 9,
			5, 8, 9,
			5, 6, 8,
			6, 7, 8}
	{}

private:
	float vertex[30];
	unsigned int indices[24];

	float* getVertexData(){return vertex;}
	int getVertexDataSize(){return sizeof(vertex);}

	unsigned int* getIndicesData(){return indices;}
	int getIndicesDataSize(){return sizeof(indices);}
};*/

#endif