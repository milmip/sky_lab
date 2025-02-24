#include "scenes/MenuScene.hpp"

MenuScene::MenuScene(SceneManager* manager):
sceneManager(manager)
{
	proj_m = glm::perspective(glm::radians(45.0f), (float)sceneManager->scr_width / (float)sceneManager->scr_height, 0.001f, 100.0f);

}

MenuScene::~MenuScene()
{

}

void MenuScene::Init()
{
	std::cout << "MenuScene initialisée !" << std::endl;
	simple_shader.Init("shaders/vert1.glsl", "shaders/frag1.glsl");
	
	const char* texts_loc[] = {/*"ressources/textures/8k_earth_clouds.jpg", */"ressources/textures/8k_earth_daymap.jpg"};
	unsigned int n_texts = 1;

	earth.init(simple_shader.ID, n_texts, texts_loc);
	
}

void MenuScene::ProcessInput(const InputManager& input)
{
	if (input.IsKeyPressed(GLFW_KEY_ENTER))
	{
		std::cout << "Démarrage du jeu !" << std::endl;
		sceneManager->ChangeScene(space);
	}

	if (input.IsKeyPressed(GLFW_KEY_W))
	{
		cam.processPositionOffset(FORWARD, 0.01f);
	}
	if (input.IsKeyPressed(GLFW_KEY_A))
	{
		cam.processPositionOffset(LEFT, 0.01f);
	}
	if (input.IsKeyPressed(GLFW_KEY_D))
	{
		cam.processPositionOffset(RIGHT, 0.01f);
	}
	if (input.IsKeyPressed(GLFW_KEY_S))
	{
		cam.processPositionOffset(BACKWARD, 0.01f);
	}
	if (input.IsKeyPressed(GLFW_KEY_SPACE))
	{
		cam.processPositionOffset(UP, 0.01f);
	}
	if (input.IsKeyPressed(GLFW_KEY_LEFT_ALT))
	{
		cam.processPositionOffset(DOWN, 0.01f);
	}

	if (input.IsKeyPressed(GLFW_KEY_E))
	{
		cam.processRollOffset(-0.01f);
	}
	if (input.IsKeyPressed(GLFW_KEY_Q))
	{
		cam.processRollOffset(0.01f);
	}

	double x_off, y_off;
	input.GetMouseOffset(&x_off, &y_off);

	cam.processYawPitchOffset((float)atan(x_off * 0.001),
							-(float)atan(y_off * 0.001));
	
}

void MenuScene::Update(float deltaTime)
{
	//cam.Update(deltaTime);
	earth.update_model_matrix();
}

void MenuScene::Render()
{
	Shader::setVec3(simple_shader.ID, "viewPos", cam.GetPosition());
	Shader::setVec3(simple_shader.ID, "light_pos", sunlight.get_position());
	Shader::setVec3(simple_shader.ID, "light_color", sunlight.get_color());
	Shader::setFloat(simple_shader.ID, "ambiant", sunlight.get_ambiant());

	Shader::setMat4(simple_shader.ID, "view", cam.GetViewMatrix());
	Shader::setMat4(simple_shader.ID, "projection", &proj_m);

	Shader::setMat4(earth.get_shader(), "model", earth.get_model_matrix());
	earth.bind();
	earth.draw();
}

void MenuScene::Destroy()
{
	std::cout << "MenuScene détruite !" << std::endl;
	glDeleteProgram(simple_shader.ID);
}