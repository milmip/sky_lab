#include "graphics/camera.hpp"

Camera::Camera()
{
	position = glm::vec3(1.0f, 0.0f, 0.0f);

	orientation = glm::mat3(-1.0f, 0.0f, 0.0f,
							 0.0f, 1.0f, 0.0f,
							 0.0f, 0.0f, 1.0f);

	view_mat = glm::mat4(1.0f);

}

Camera::~Camera()
{
	
}


glm::mat4* Camera::GetViewMatrix()
{
	view_mat = glm::lookAt(	position,
							position + (orientation * front),
							orientation * up);
	return &view_mat;
}

void Camera::processPositionOffset(Camera_Movement dir, float offset)
{
	position += (-2 * (dir % 2) + 1 ) * offset * orientation * orient_dirs[dir / 2];
}

void Camera::processYawPitchOffset(float yaw, float pitch)
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

void Camera::processRollOffset(float roll)
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

/*
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
Front(glm::vec3(0.0f, 0.0f, -1.0f)),
MovementSpeed(SPEED),
MouseSensitivity(SENSITIVITY),
Zoom(ZOOM),
futur_movements{false, false, false, false, false, false},
futur_mouse_movements{0.0f, 0.0f}
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch):
Front(glm::vec3(0.0f, 0.0f, -1.0f)),
MovementSpeed(SPEED),
MouseSensitivity(SENSITIVITY),
Zoom(ZOOM),
futur_movements{false, false, false, false, false, false},
futur_mouse_movements{0.0f, 0.0f}
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

Camera::~Camera()
{

}

glm::mat4* Camera::GetViewMatrix()
{
	view_mat = glm::lookAt(Position, Position + Front, Up);
	return &view_mat;
}

void Camera::Update(float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (futur_movements[FORWARD])
	{
		Position += Front * velocity;
		futur_movements[FORWARD] = false;
	}
	if (futur_movements[BACKWARD])
	{
		Position -= Front * velocity;	
		futur_movements[BACKWARD] = false;
	}
	if (futur_movements[LEFT])
	{
		Position -= Right * velocity;
		futur_movements[LEFT] = false;
	}
	if (futur_movements[RIGHT])
	{
		Position += Right * velocity;
		futur_movements[RIGHT] = false;
	}
	if (futur_movements[UP])
	{
		Position += Up * velocity;
		futur_movements[UP] = false;
	}
	if (futur_movements[DOWN])
	{
		Position -= Up * velocity;
		futur_movements[DOWN] = false;
	}

	velocity = MouseSensitivity * deltaTime;

	Yaw   += futur_mouse_movements[0] * velocity;
	Pitch -= futur_mouse_movements[1] * velocity;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;



	updateCameraVectors();


}

void Camera::ProcessMouvement(Camera_Movement direction)
{
	futur_movements[direction] = true;
}

void Camera::ProcessMouseMouvement(double x_off, double y_off)
{
	futur_mouse_movements[0] = (float)x_off;
	futur_mouse_movements[1] = (float)y_off;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
}


/*void Camera::ProcessMouseScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}


void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	
	Right = glm::normalize(glm::cross(Front, WorldUp));  
	Up  = glm::normalize(glm::cross(Right, Front));
}*/