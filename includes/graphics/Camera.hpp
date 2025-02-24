#ifndef CAMERA
#define CAMERA

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cmath>

void printM3(glm::mat3 mat);


enum CameraMovement {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

const glm::vec3 front			= glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 right			= glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 up				= glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 orient_dirs[] 	= {front, right, up};

class Camera
{
public:
	Camera();
	~Camera() = default;

	glm::mat4* GetViewMatrix();
	glm::vec3* GetPosition(){return &position;}

	void ProcessPositionOffset(CameraMovement dir, float offset);
	void ProcessYawPitchOffset(float yaw, float pitch);
	void ProcessRollOffset(float roll);

private:
	glm::vec3 position;
	glm::mat3 orientation;
	glm::mat4 viewMatrix;
};

#endif
