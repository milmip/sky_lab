#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <unordered_map>

void myKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void myCharCallback(GLFWwindow* window, unsigned int codepoint);
void myCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

class InputManager
{
public:
	InputManager();
	~InputManager() = default;
	
	void Init(GLFWwindow* window);

	bool IsKeyPressed(int key) const;
	void ProcessKey(int key, bool upDown);

	void ProcessChar(unsigned int codepoint);
	void EmptyBufferChar();
	void ReadBuffer();

	void ProcessCursor(double x, double y);
	void CalculateCursorOffset();
	void GetCursorOffset(double* xOff, double* yOff) const;
	//void GetMousePosition(double& x, double& y) const;

private:
	int bufferIdx, bufferLenght;
	double newMouseX, oldMouseX, mouseXOff;
	double newMouseY, oldMouseY, mouseYOff;

	unsigned int bufferChar[4];


	std::unordered_map<int, bool> keyStates;

	bool isBufferEmpty();
	
};

#endif
