#include "core/InputManager.hpp"

void myKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::cout << "key : " << key << " " << action << std::endl;
}

void myCharCallBack(GLFWwindow* window, unsigned int codepoint)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	inputManager->ProcessChar(codepoint);
}

void InputManager::Init(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, myKeyCallBack);
	glfwSetCharCallback(window, myCharCallBack);
}

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

void InputManager::GetMouseOffset(double* xOff, double* yOff) const
{
	if (mouseX_off > 100 || mouseY_off > 100)
	{
		*xOff = 0.0;
		*yOff = 0.0;
	}
	else
	{
		*xOff = mouseX_off;
		*yOff = mouseY_off;
	}
}

void InputManager::ProcessChar(unsigned int codepoint)
{
	std::cout << "charr : " << codepoint << std::endl;
}