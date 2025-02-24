#ifndef CAMERA
#define CAMERA

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <cmath>

void printM3(glm::mat3 mat);


enum Camera_Movement {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	UP,
	DOWN
};


/*const float YAW   		=  0.0f;
const float PITCH      	=  0.0f;
const float SPEED      	=  2.5f;
const float SENSITIVITY =  10.0f;
const float ZOOM        =  45.0f;*/

const glm::vec3 front	= glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 right	= glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 up		= glm::vec3(0.0f, 0.0f, 1.0f);

const glm::vec3 orient_dirs[] = {front, right, up};

class Camera
{
public:
	Camera();
	~Camera();

	glm::mat4* GetViewMatrix();
	glm::vec3* GetPosition(){return &position;}

	void processPositionOffset(Camera_Movement dir, float offset);
	void processYawPitchOffset(float yaw, float pitch);
	void processRollOffset(float roll);

private:
	glm::vec3 position;
	glm::mat3 orientation;

	glm::mat4 view_mat;


};


/*
class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	
	float Yaw;
	float Pitch;
	
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	~Camera();

	glm::mat4* GetViewMatrix();

	void Update(float deltaTime);
	void ProcessMouvement(Camera_Movement direction);
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMouvement(double x_off, double y_off);
	void ProcessMouseScroll(float yoffset);

private:
	glm::mat4 view_mat;

	bool futur_movements[6];
	float futur_mouse_movements[2];
	
	void updateCameraVectors();
};
*/
#endif
