#ifndef GAMESCENE
#define GAMESCENE

#include <memory>

#include "scenes/Scene.hpp"

class GameScene : public Scene 
{
private:
	SceneManager* sceneManager;

public:
	GameScene(SceneManager* manager) : sceneManager(manager) {}

	void Init() override 
	{
		std::cout << "GameScene initialisée !" << std::endl;
	}

	void ProcessInput(const InputManager& input) override
	{
		if (input.IsKeyPressed(GLFW_KEY_LEFT))
		{
			std::cout << "Retour au menu !" << std::endl;
			sceneManager->ChangeScene(MENU);
		}
	}

	void Update(float deltaTime) override 
	{

	}

	void Render() override
	{
		// Rendu du jeu
	}

	void Destroy() override {
		std::cout << "GameScene détruite !" << std::endl;
	}
};

#endif