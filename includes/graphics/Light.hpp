#ifndef LIGHT
#define LIGHT

#include <glad/glad.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 POS, glm::vec3 COL, float AMB);
	~Light() = default;

	glm::vec3* GetPosition(){return &position;}
	glm::vec3* GetColor(){return &color;}
	float GetAmbiant(){return ambiant;}

private:
	float ambiant;
	glm::vec3 position;
	glm::vec3 color;
};

#endif