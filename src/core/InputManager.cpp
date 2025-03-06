#include "core/InputManager.hpp"

void myKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	if (action != 2)
	{

		inputManager->ProcessKey(key, static_cast<bool>(action));

		unsigned int c(0);
		switch (key)
		{
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_T:
			c = UTF_CTRL_T * static_cast<unsigned int>
								(inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) & inputManager->IsKeyPressed(GLFW_KEY_T));
			inputManager->SetInvisibleChar(c);
			/*if (c != 0)
			{
				std::cout << c << std::endl;
			}*/
			break;

		case GLFW_KEY_BACKSPACE:
			c = UTF_SUPP * static_cast<unsigned int>
								(inputManager->IsKeyPressed(GLFW_KEY_BACKSPACE));
			inputManager->SetInvisibleChar(c);
			break;

		case GLFW_KEY_ENTER:
			c = UTF_ENTER * static_cast<unsigned int>
								(inputManager->IsKeyPressed(GLFW_KEY_ENTER));
			inputManager->SetInvisibleChar(c);
			break;
		}
	}
}

void myCharCallback(GLFWwindow* window, unsigned int codepoint)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	inputManager->SetVisibleChar(codepoint);
}

void myCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	inputManager->ProcessCursor(xpos, ypos);
}


void InputManager::Init(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);

	glfwSetKeyCallback(window, myKeyCallback);
	glfwSetCharCallback(window, myCharCallback);
	glfwSetCursorPosCallback(window, myCursorPosCallback);

	for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key)
	{
		keyStates[key] = false;
	}
}
/*

void InputManager::GetMousePosition(double& x, double& y) const
{
	x = mouseX;
	y = mouseY;
}*/

bool InputManager::IsKeyPressed(int key) const
{
	auto it = keyStates.find(key);
	return it != keyStates.end() && it->second;
}

void InputManager::ProcessKey(int key, bool upDown)
{
	keyStates[key] = upDown;
}

void InputManager::ProcessCursor(double x, double y)
{
	newMouseX = x;
	newMouseY = y;
}

void InputManager::CalculateCursorOffset()
{
	mouseXOff = newMouseX - oldMouseX;
	mouseYOff = oldMouseY - newMouseY;

	oldMouseX = newMouseX;
	oldMouseY = newMouseY;
}

void InputManager::GetCursorOffset(double* xOff, double* yOff) const
{
	if (mouseXOff > 600 || mouseYOff > 600)
	{
		*xOff = 0.0;
		*yOff = 0.0;
	}
	else
	{
		*xOff = mouseXOff;
		*yOff = mouseYOff;
	}
}