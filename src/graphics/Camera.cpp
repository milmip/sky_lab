#include "graphics/Camera.hpp"

Camera::Camera()
{
	position = glm::vec3(1.0f, 0.0f, 0.0f);
	orientation = glm::mat3(-1.0f, 0.0f, 0.0f,
							 0.0f, 1.0f, 0.0f,
							 0.0f, 0.0f, 1.0f);
	viewMatrix = glm::mat4(1.0f);
}

glm::mat4* Camera::GetViewMatrix()
{
	viewMatrix = glm::lookAt(	position,
							position + (orientation * front),
							orientation * up);
	return &viewMatrix;
}

void Camera::ProcessPositionOffset(CameraMovement dir, float offset)
{
	position += (-2 * (dir % 2) + 1 ) * offset * orientation * orient_dirs[dir / 2];
}

void Camera::ProcessYawPitchOffset(float yaw, float pitch)
{
	glm::vec3 front_out_1 = glm::vec3(cos(yaw), sin(yaw), 0.0f);
	glm::vec3 front_in_1 = orientation * front_out_1;

	glm::vec3 right_1 = glm::normalize(glm::cross(front_in_1, orientation * up));

	orientation = glm::mat3(front_in_1, right_1, orientation * up);


	glm::vec3 front_out_2 = glm::vec3(cos(pitch), 0.0f, sin(pitch));
	glm::vec3 front_in_2 = orientation * front_out_2;

	glm::vec3 up_1 = glm::normalize(glm::cross(orientation * right, front_in_2));

	orientation = glm::mat3(front_in_2, right_1, up_1);
}

void Camera::ProcessRollOffset(float roll)
{
	glm::vec3 right_out = glm::vec3(0.0f, cos(roll), sin(roll));
	glm::vec3 right_in = orientation * right_out;

	glm::vec3 up_1 = glm::normalize(glm::cross(right_in, orientation * front));

	orientation = glm::mat3(orientation * front, right_in, up_1);
}


void printM3(glm::mat3 mat)
{
	std::cout << mat[0][0] << "\t" << mat[1][0] << "\t" << mat[2][0] << std::endl;
	std::cout << mat[0][1] << "\t" << mat[1][1] << "\t" << mat[2][1] << std::endl;
	std::cout << mat[0][2] << "\t" << mat[1][2] << "\t" << mat[2][2] << std::endl;
}