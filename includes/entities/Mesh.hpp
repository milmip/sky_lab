#ifndef MESH
#define MESH

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "entities/object.hpp"

#include <cmath>

class Sphere : public Object
{
public:
	Sphere(int stacks, int meridans);
	~Sphere();

private:
	int vertex_data_size;
	int indices_data_size;

	float *vertex;
	unsigned int *indices;

	float* get_vertex_data(){return vertex;}
	int get_vertex_data_size(){return vertex_data_size;}

	unsigned int* get_indices_data(){return indices;}
	int get_indices_data_size(){return indices_data_size;}
};


class Square : public Object
{
	public:
	Square():
	vertex{ 0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
		   -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
			0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
		   -0.5f, -0.5f,  0.5f, 1.0f, 1.0f},

	indices{0, 1, 2,
			1, 2, 3}
	{}

private:
	float vertex[20];
	unsigned int indices[6];

	float* get_vertex_data(){return vertex;}
	int get_vertex_data_size(){return sizeof(vertex);}

	unsigned int* get_indices_data(){return indices;}
	int get_indices_data_size(){return sizeof(indices);}
};

class Cube : public Object
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

	float* get_vertex_data(){return vertex;}
	int get_vertex_data_size(){return sizeof(vertex);}

	unsigned int* get_indices_data(){return indices;}
	int get_indices_data_size(){return sizeof(indices);}
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

	float* get_vertex_data(){return vertex;}
	int get_vertex_data_size(){return sizeof(vertex);}

	unsigned int* get_indices_data(){return indices;}
	int get_indices_data_size(){return sizeof(indices);}
};

#endif