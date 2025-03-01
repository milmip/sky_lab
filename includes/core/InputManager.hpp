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
	InputManager() = default;
	~InputManager() = default;
	
	static InputManager& GetInstance(){static InputManager instance;return instance;}

	void Init(GLFWwindow* window);
	void ProcessInput(GLFWwindow* window);
	bool IsKeyPressed(int key) const;
	bool IsMouseButtonPressed(int button) const;
	void GetMousePosition(double& x, double& y) const;
	void GetMouseOffset(double* xOff, double* yOff) const;

	void ProcessChar(unsigned int codepoint);

private:
	double mouseX, mouseY;
	double mouseX_off, mouseY_off;

	std::unordered_map<int, bool> keyStates;
	std::unordered_map<int, bool> mouseButtonStates;
};

#endif
