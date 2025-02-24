#ifndef SCENEMANAGER
#define SCENEMANAGER

#include <iostream>
#include <memory>

#include "core/InputManager.hpp"

#include "scenes/Scene.hpp"


enum ScenesName
{
    menu,
    space
};

class SceneManager 
{
private:
    std::unique_ptr<Scene> currentScene;

public:
    int scr_width;
    int scr_height;

    SceneManager() = default;
    ~SceneManager() = default;

    void Init(int w, int h);
    void ChangeScene(ScenesName name);
    void ProcessInput(const InputManager& input);
    void Update(float deltaTime);
    void Render();
    void Destroy();
};

#include "scenes/GameScene.hpp"
#include "scenes/MenuScene.hpp"

#endif
