#ifndef SCENEMANAGER
#define SCENEMANAGER

#include "core/InputManager.hpp"
#include "scenes/Scene.hpp"

#include <iostream>
#include <memory>

enum ScenesName
{
	MENU,
	SPACE
};

class SceneManager 
{
public:
	int scr_width;
	int scr_height;

	SceneManager() = default;
	~SceneManager() = default;

	void Init(int w, int h);
	void ChangeScene(ScenesName name);
	void ProcessInput(InputManager& input);
	void Update(float deltaTime);
	void Render();
	void Destroy();

private:
	std::unique_ptr<Scene> currentScene;
};

#include "scenes/GameScene.hpp"
#include "scenes/SpaceScene.hpp"

#endif
