#ifndef SPACESCENE
#define SPACESCENE

#include <glad/glad.h>
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "core/SceneManager.hpp"
#include "scenes/Scene.hpp"

#include "entities/Termini.hpp"
#include "entities/Mesh.hpp"

#include "graphics/Camera.hpp"
#include "graphics/Shader.hpp"
#include "graphics/Light.hpp"

#include <iostream>
#include <cmath>
#include <map>
#include <string>

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

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
	Termini termini;

	Sphere earth = Sphere(100, 100);
	Shader simple_shader;

	glm::mat4 projMatrix;

	std::map<GLchar, Character> Characters;
	unsigned int VAO, VBO;
	glm::mat4 glyphProjMatrix;

	void setUniformEarth();
	void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

};

#endif
