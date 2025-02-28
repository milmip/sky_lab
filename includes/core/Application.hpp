#ifndef APPLICATION
#define APPLICATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/SceneManager.hpp"
#include "core/InputManager.hpp"

#include <iostream>
#include <thread>
#include <chrono>

class Application
{
public:
	Application(const char* TITLE, const float FPS);
	~Application();

	void Run();

private:
	int width, height;
	float lastFrameTime, fps;
	const char* title;

	GLFWwindow* window;

	SceneManager sceneManager;
	InputManager inputManager;

	void init();
	void processInput();
	void update(float deltaTime);
	void render();
	void temporize();
};

#endif