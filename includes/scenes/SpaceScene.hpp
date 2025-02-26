#ifndef SPACESCENE
#define SPACESCENE

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "core/SceneManager.hpp"
#include "scenes/Scene.hpp"

//#include "entities/Termini.hpp"
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

	Shader glyphShader;
	//Termini termini = Termini(200, 200, 24, "/usr/share/fonts/truetype/fonts-deva-extra/chandas1-2.ttf");

	Sphere earth = Sphere(100, 100);
	Shader simple_shader;

	glm::mat4 projMatrix;
};

#endif
