#ifndef MENUSCENE
#define MENUSCENE

#include "scenes/Scene.hpp"
#include "scenes/GameScene.hpp"
#include "scenes/SceneManager.hpp"

class MenuScene : public Scene 
{
private:
    SceneManager* sceneManager;

public:
    MenuScene(SceneManager* manager) : sceneManager(manager) {}

    void Init() override 
    {
        std::cout << "MenuScene initialisée !" << std::endl;
    }

    void ProcessInput(const InputManager& input) override
    {
        if (input.IsKeyPressed(GLFW_KEY_ENTER))
        {
            std::cout << "Démarrage du jeu !" << std::endl;
            sceneManager->ChangeScene(std::make_unique<GameScene>(sceneManager));
        }
    }

    void Update(float deltaTime) override
    {

    }

    void Render() override 
    {
        // Rendu du menu (ex: texte, boutons)
    }

    void Destroy() override
    {
        std::cout << "MenuScene détruite !" << std::endl;
    }
};

#endif
