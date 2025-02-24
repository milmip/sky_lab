#include "entities/Mesh.hpp"

Sphere::Sphere(int stacks, int meridans)
{
	float pi(3.1415926536);

	vertex = new float[ 8 * 4 * (stacks) * (meridans) ];
	indices = new unsigned int[ 3 * 2 * (stacks * meridans) ];

	int k1(0), k2(8), k3(16), k4(24), k(0), l(0);
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
	float z1, z2, z3, z4;
	float r1, r2, r3, r4;
	float xt1, xt2, xt3, xt4;
	float yt1, yt2, yt3, yt4;


	for (int i = 0; i < stacks; ++i)
	{
		z1 = cos((float)i * pi / stacks);
		z2 = z1;
		z3 = cos((float)(i+1) * pi / stacks);
		z4 = z3;

		r1 = sin((float)i * pi / stacks);;
		r2 = r1;
		r3 = sin((float)(i+1) * pi / stacks);;
		r4 = r3;

		yt1 = z1/2 + 0.5f;
		yt2 = z2/2 + 0.5f;
		yt3 = z3/2 + 0.5f;
		yt4 = z4/2 + 0.5f;

		for (int j = 0; j < meridans; ++j)
		{
			x1 = r1 * cos((float)j * 2* pi / meridans);
			x2 = r2 * cos((float)(j+1) * 2* pi / meridans);
			x3 = r3 * cos((float)j * 2* pi / meridans);
			x4 = r4 * cos((float)(j+1) * 2* pi / meridans);

			y1 = r1 * sin((float)j * 2* pi / meridans);
			y2 = r2 * sin((float)(j+1) * 2* pi / meridans);
			y3 = r3 * sin((float)j * 2* pi / meridans);
			y4 = r4 * sin((float)(j+1) * 2* pi / meridans);

			xt1 = (float)j / meridans;
			xt2 = (float)(j+1) / meridans;
			xt3 = (float)j / meridans;
			xt4 = (float)(j+1) / meridans;

			vertex[k1] 	= x1 / 2;
			vertex[k1+1] = y1 / 2;
			vertex[k1+2] = z1 / 2;
			vertex[k1+3] = 0.0f;
			vertex[k1+4] = 0.0f;
			vertex[k1+5] = 0.0f;
			vertex[k1+6] = xt1;
			vertex[k1+7] = yt1;

			vertex[k2] 	= x2 / 2;
			vertex[k2+1] = y2 / 2;
			vertex[k2+2] = z2 / 2;
			vertex[k2+3] = 0.0f;
			vertex[k2+4] = 0.0f;
			vertex[k2+5] = 0.0f;
			vertex[k2+6] = xt2;
			vertex[k2+7] = yt2;

			vertex[k3] 	= x3 / 2;
			vertex[k3+1] = y3 / 2;
			vertex[k3+2] = z3 / 2;
			vertex[k3+3] = 0.0f;
			vertex[k3+4] = 0.0f;
			vertex[k3+5] = 0.0f;
			vertex[k3+6] = xt3;
			vertex[k3+7] = yt3;

			vertex[k4] 	= x4 / 2;
			vertex[k4+1] = y4 / 2;
			vertex[k4+2] = z4 / 2;
			vertex[k4+3] = 0.0f;
			vertex[k4+4] = 0.0f;
			vertex[k4+5] = 0.0f;
			vertex[k4+6] = xt4;
			vertex[k4+7] = yt4;

			indices[k] = l;
			indices[k+1] = l+1;
			indices[k+2] = l+3;

			indices[k+3] = l;
			indices[k+4] = l+2;
			indices[k+5] = l+3;

			k1 += 8 * 4;
			k2 += 8 * 4;
			k3 += 8 * 4;
			k4 += 8 * 4;

			l += 4;
			k += 6;
		}
	}

	vertex_data_size = sizeof(float) * k4;
	indices_data_size = sizeof(int) * k;

	glm::vec3 a, b, c, u, v, n;
	int ai, bi, ci, di;

	for (int i = 0; i < k; i += 6)
	{
		ai = indices[i] * 8;
		bi = indices[i+1] * 8;
		ci = indices[i+4] * 8;
		di = indices[i+2] * 8;

		a = glm::vec3(vertex[ai], vertex[ai + 1], vertex[ai + 2]);
		b = glm::vec3(vertex[bi], vertex[bi + 1], vertex[bi + 2]);
		c = glm::vec3(vertex[ci], vertex[ci + 1], vertex[ci + 2]);

		u = b - a;
		v = c - a;

		n = glm::normalize(glm::cross(v, u));

		vertex[ai+3] = n[0];
		vertex[ai+4] = n[1];
		vertex[ai+5] = n[2];

		vertex[bi+3] = n[0];
		vertex[bi+4] = n[1];
		vertex[bi+5] = n[2];

		vertex[ci+3] = n[0];
		vertex[ci+4] = n[1];
		vertex[ci+5] = n[2];

		vertex[di+3] = n[0];
		vertex[di+4] = n[1];
		vertex[di+5] = n[2];
	}

	/*

	int k1(0), k2(0);
	int a, b, c, d;
	k = 0;

	for (i = 0; i < stacks; ++i)
	{
		k1 = i * (meridans + 1);
		k2 = (i + 1) * (meridans + 1);
		for (j = 0; j < meridans; ++j)
		{
			a = k1 + j;
			b = k1 + j + 1;
			c = k2 + j;
			d = k2 + j + 1;

			indices[k] 	 = a;
			indices[k+1] = b;
			indices[k+2] = c;
			indices[k+3] = b;
			indices[k+4] = c;
			indices[k+5] = d;

			k += 6;
		}
	}

	indices_data_size = sizeof(int) * (k);

	int i, j;
	int k(0);
	float x, y, z, r, xt, yt;

	for (i = 0; i < stacks+1; ++i)
	{
		z = cos((float)i * pi / stacks); //z coord
		r = sin((float)i * pi / stacks); //dist from the axis

		yt = z/2 + 0.5f;

		for (j = 0; j < meridans+1; ++j)
		{
			x = r * cos((float)j * 2 * pi / meridans);
			y = r * sin((float)j * 2 * pi / meridans);

			xt = (float)j / meridans;

			

			vertex[k] 	= x / 2;
			vertex[k+1] = y / 2;
			vertex[k+2] = z / 2;
			vertex[k+3] = 0.0f;
			vertex[k+4] = 0.0f;
			vertex[k+5] = 0.0f;
			vertex[k+6] = xt;
			vertex[k+7] = yt;

			k += 8;
		}
	}

	vertex_data_size = sizeof(float) * k;
	*/

}
Sphere::~Sphere()
{
	delete[] vertex;
	delete[] indices;
}

void printmat4(glm::mat4* mat)
{
	std::cout << (*mat)[0][0] << "\t" << (*mat)[1][0] << "\t" << (*mat)[2][0] << "\t" << (*mat)[3][0] << std::endl;
	
	std::cout << (*mat)[0][1] << "\t" << (*mat)[1][1] << "\t" << (*mat)[2][1] << "\t" << (*mat)[3][1] << std::endl;
	
	std::cout << (*mat)[0][2] << "\t" << (*mat)[1][2] << "\t" << (*mat)[2][2] << "\t" << (*mat)[3][2] << std::endl;

	std::cout << (*mat)[0][3] << "\t" << (*mat)[1][3] << "\t" << (*mat)[2][3] << "\t" << (*mat)[3][3] << std::endl << std::endl;
}