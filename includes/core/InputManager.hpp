#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "enums/utf8.hpp"

#include <iostream>
#include <unordered_map>

void myKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void myCharCallback(GLFWwindow* window, unsigned int codepoint);
void myCursorPosCallback(GLFWwindow* window, double xpos, double ypos);

class InputManager
{
public:
	InputManager() = default;
	~InputManager() = default;
	
	void Init(GLFWwindow* window);

	bool IsKeyPressed(int key) const;
	void ProcessKey(int key, bool upDown);

	void SetVisibleChar(unsigned int c){visibleChar = c;}
	void SetInvisibleChar(unsigned int c){invisibleChar = c;}
	unsigned int GetVisibleChar(){return visibleChar;}
	unsigned int GetInvisibleChar(){return invisibleChar;}

	void ProcessCursor(double x, double y);
	void CalculateCursorOffset();
	void GetCursorOffset(double* xOff, double* yOff) const;
	//void GetMousePosition(double& x, double& y) const;

private:
	double newMouseX, oldMouseX, mouseXOff;
	double newMouseY, oldMouseY, mouseYOff;

	unsigned int visibleChar, invisibleChar;


	std::unordered_map<int, bool> keyStates;
};

#endif
