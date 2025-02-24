#ifndef MENUSCENE
#define MENUSCENE

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <cmath>

#include "core/SceneManager.hpp"
#include "scenes/Scene.hpp"

#include "entities/Mesh.hpp"

#include "graphics/camera.hpp"
#include "graphics/shader.hpp"
#include "graphics/Light.hpp"

class MenuScene : public Scene
{
private:
	SceneManager* sceneManager;
    Camera cam = Camera();
    Light sunlight = Light(glm::vec3(2.0f, 0.0f, 0.0f), 
							glm::vec3(1.0f, 1.0f, 1.0f),
							0.2f);

    Sphere earth = Sphere(100, 100);
    Shader simple_shader;

    glm::mat4 proj_m;

public:
	MenuScene(SceneManager* manager);
    ~MenuScene();

	void Init() override;
	void ProcessInput(const InputManager& input) override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;
};

#endif
