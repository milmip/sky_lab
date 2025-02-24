#ifndef APPLICATION
#define APPLICATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/SceneManager.hpp"
#include "core/InputManager.hpp"

//#include "scenes/MenuScene.hpp"

#include <iostream>

class Application 
{
public:
    Application(const char* title);
    ~Application();

    void Run();

private:
    void Init();
    void ProcessInput();
    void Update(float deltaTime);
    void Render();

    int width, height;
    const char* title;
    GLFWwindow* window;

    SceneManager sceneManager;
    InputManager inputManager;

    float lastFrameTime;
};

#endif