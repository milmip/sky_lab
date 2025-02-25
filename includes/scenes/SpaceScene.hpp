#ifndef SPACESCENE
#define SPACESCENE

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "core/SceneManager.hpp"
#include "scenes/Scene.hpp"

#include "entities/Mesh.hpp"

#include "graphics/Camera.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Light.hpp"

#include <iostream>
#include <cmath>

class SpaceScene : public Scene
{
public:
	SpaceScene(SceneManager* MANAGER);
	~SpaceScene() = default;

	void Init() override;
	void ProcessInput(const InputManager& input) override;
	void Update(float deltaTime) override;
	void Render() override;
	void Destroy() override;

private:
	SceneManager* sceneManager;
	Camera cam = Camera();
	Light sunlight = Light(glm::vec3(2.0f, 0.0f, 0.0f), 
							glm::vec3(1.0f, 1.0f, 1.0f),
							0.2f);

	Sphere earth = Sphere(100, 100);
	Shader simple_shader;

	glm::mat4 proj_m;
};

#endif
