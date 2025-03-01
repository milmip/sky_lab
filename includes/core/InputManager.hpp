#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <unordered_map>

void myKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void myCharCallBack(GLFWwindow* window, unsigned int codepoint);

class InputManager
{
public:
	InputManager();
	~InputManager();
	
	void Init(GLFWwindow* window);
	/*void ProcessInput(GLFWwindow* window);
	
	bool IsMouseButtonPressed(int button) const;
	void GetMousePosition(double& x, double& y) const;
	void GetMouseOffset(double* xOff, double* yOff) const;
	*/
	bool IsKeyPressed(int key) const;
	void ProcessKey(int key, bool upDown);
	void ProcessChar(unsigned int codepoint);
	void EmptyBufferChar();
	void ReadBuffer();

private:
	int bufferIdx, bufferLenght;
	unsigned int bufferChar[4];

	std::unordered_map<int, bool> keyStates;

	bool isBufferEmpty();
	/*double mouseX, mouseY;
	double mouseX_off, mouseY_off;

	
	std::unordered_map<int, bool> mouseButtonStates;*/
};

#endif
