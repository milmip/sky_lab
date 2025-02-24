#ifndef LIGHT
#define LIGHT

#include <glad/glad.h>
#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 pos, glm::vec3 col, float amb);
	~Light() = default;

	glm::vec3* get_position(){return &position;}
	glm::vec3* get_color(){return &color;}
	float get_ambiant(){return ambiant;}

private:
	glm::vec3 position;
	glm::vec3 color;
	float ambiant;

};

#endif