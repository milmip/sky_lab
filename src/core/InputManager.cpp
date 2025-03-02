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
			c = 20 * static_cast<unsigned int>
								(inputManager->IsKeyPressed(GLFW_KEY_LEFT_CONTROL) & inputManager->IsKeyPressed(GLFW_KEY_T));
			inputManager->ProcessChar(c);
			break;

		case GLFW_KEY_BACKSPACE:
			c = 8 * static_cast<unsigned int>
								(inputManager->IsKeyPressed(GLFW_KEY_BACKSPACE));
			inputManager->ProcessChar(c);
			break;

		case GLFW_KEY_ENTER:
			c = 10 * static_cast<unsigned int>
								(inputManager->IsKeyPressed(GLFW_KEY_ENTER));
			inputManager->ProcessChar(c);
			break;
		}
	}
}

void myCharCallback(GLFWwindow* window, unsigned int codepoint)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	inputManager->ProcessChar(codepoint);
}

void myCursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	inputManager->ProcessCursor(xpos, ypos);
}

InputManager::InputManager():
bufferChar{0,0,0,0},
bufferIdx(0),
bufferLenght(4)
{}

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

void InputManager::ProcessChar(unsigned int codepoint)
{
	if (bufferIdx < bufferLenght)
	{
		bufferChar[bufferIdx] = codepoint;
		bufferIdx += 1;
	}
}

void InputManager::EmptyBufferChar()
{
	for (int i = 0; i < bufferLenght; ++i)
	{
		bufferChar[i] = 0;
	}
	bufferIdx = 0;
}

void InputManager::ReadBuffer()
{
	if(!isBufferEmpty())
	{
		std::cout << bufferChar[0] << " " << bufferChar[1] << " " << bufferChar[2] << " " << bufferChar[3] << std::endl;
	}
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

bool InputManager::isBufferEmpty()
{
	bool res = false;

	for (int i = 0; i < bufferLenght; ++i)
	{
		res |= static_cast<bool>(bufferChar[i]);
	}

	return !res;
}