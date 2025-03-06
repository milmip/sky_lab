#include "core/SceneManager.hpp"

void SceneManager::Init(int w, int h)
{
	scr_width = w;
	scr_height = h;
}

void SceneManager::ChangeScene(ScenesName name)
{
	std::unique_ptr<Scene> newScene;
	if (currentScene)
	{
		currentScene->Destroy();
	}

	if (name == MENU)
	{
		newScene = std::make_unique<SpaceScene>(this);
	}
	else if (name == SPACE)
	{
		newScene = std::make_unique<GameScene>(this);
	}

	currentScene = std::move(newScene);
	if (currentScene)
	{
		currentScene->Init();
	}
}

void SceneManager::ProcessInput(InputManager& input)
{
	if (currentScene)
	{
		currentScene->ProcessInput(input);
	}
}

void SceneManager::Update(float deltaTime)
{
	if (currentScene)
	{
		currentScene->Update(deltaTime);
	}
}

void SceneManager::Render()
{
	if (currentScene)
	{
		currentScene->Render();
	}
}

void SceneManager::Destroy()
{
	if (currentScene)
	{
		currentScene->Destroy();
	}
}