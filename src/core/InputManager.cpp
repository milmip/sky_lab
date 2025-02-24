#include "core/InputManager.hpp"

void InputManager::ProcessInput(GLFWwindow* window)
{
	for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
	{
		keyStates[key] = (glfwGetKey(window, key) == GLFW_PRESS);
	}

	for (int button = GLFW_MOUSE_BUTTON_1; button <= GLFW_MOUSE_BUTTON_LAST; ++button)
	{
		mouseButtonStates[button] = (glfwGetMouseButton(window, button) == GLFW_PRESS);
	}
	double ante_x = mouseX;
	double ante_y = mouseY;

	glfwGetCursorPos(window, &mouseX, &mouseY);

	mouseX_off = mouseX - ante_x;
	mouseY_off = mouseY - ante_y;
}

bool InputManager::IsKeyPressed(int key) const
{
	auto it = keyStates.find(key);
	return it != keyStates.end() && it->second;
}

bool InputManager::IsMouseButtonPressed(int button) const
{
	auto it = mouseButtonStates.find(button);
	return it != mouseButtonStates.end() && it->second;
}

void InputManager::GetMousePosition(double& x, double& y) const
{
	x = mouseX;
	y = mouseY;
}

void InputManager::GetMouseOffset(double* x_off, double* y_off) const
{
	if (mouseX_off > 100 || mouseY_off > 100)
	{
		*x_off = 0.0;
		*y_off = 0.0;
	}
	else
	{
		*x_off = mouseX_off;
		*y_off = mouseY_off;
	}
	
}