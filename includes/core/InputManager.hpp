#ifndef INPUTMANAGER
#define INPUTMANAGER

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputManager
{
public:
    InputManager() = default;
    static InputManager& GetInstance()
    {
        static InputManager instance;
        return instance;
    }

    void ProcessInput(GLFWwindow* window);
    bool IsKeyPressed(int key) const;
    bool IsMouseButtonPressed(int button) const;
    void GetMousePosition(double& x, double& y) const;
    void GetMouseOffset(double* x_off, double* y_off) const;

private:
    //InputManager() = default;
    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> mouseButtonStates;
    double mouseX, mouseY;
    double mouseX_off, mouseY_off;
};

#endif
