#include "core/Application.hpp"

Application::Application(const char* TITLE, const float FPS):
title(TITLE),
fps(FPS),
window(nullptr), 
lastFrameTime(0.0f) 
{
	init();
}

Application::~Application() 
{
	sceneManager.Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::Run()
{
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		processInput();
		update(deltaTime);
		render();

		glfwPollEvents();
		temporize();
	}
}

void Application::init() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* monitor =  glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	width = mode->width;
	height = mode->height;

	window = glfwCreateWindow(width, height, title, monitor, NULL);
	if (window == NULL)
	{
		std::cerr << "Échec de la création de la fenêtre." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Échec de l'initialisation de GLAD." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, width, height);

	inputManager.Init(window);
	sceneManager.Init(width, height);
	sceneManager.ChangeScene(MENU);
}

void Application::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else
	{
		inputManager.ProcessInput(window);
		sceneManager.ProcessInput(inputManager);
	}
}

void Application::update(float deltaTime)
{
	sceneManager.Update(deltaTime);
}

void Application::render()
{
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneManager.Render();
	glfwSwapBuffers(window);
}


void Application::temporize()
{
	float elapsed = glfwGetTime() - lastFrameTime;
	std::this_thread::sleep_for(std::chrono::duration<double>(1/fps - elapsed));
}