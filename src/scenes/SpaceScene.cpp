#include "scenes/SpaceScene.hpp"

SpaceScene::SpaceScene(SceneManager* MANAGER):
sceneManager(MANAGER)
{
	projMatrix = glm::perspective(glm::radians(45.0f),
								 (float)sceneManager->scr_width / (float)sceneManager->scr_height,
								 0.001f, 100.0f);
}

void SpaceScene::Init()
{
	std::cout << "SpaceScene initialisée !" << std::endl;

	terminiActived = false;
	//Termini
	glyphShader.Init("shaders/glyphVert.glsl", "shaders/glyphFrag.glsl");
	termini.Init(glyphShader.ID,
				 "/usr/share/fonts/truetype/downloaded/Consolas.ttf",
				 sceneManager->scr_width, sceneManager->scr_height);

	//Earth
	simple_shader.Init("shaders/vert1.glsl", "shaders/frag1.glsl");
	const char* texts_loc[] = {/*"ressources/textures/8k_earth_clouds.jpg", */"ressources/textures/8k_earth_daymap.jpg"};
	unsigned int n_texts = 1;
	earth.Init(simple_shader.ID, n_texts, texts_loc);
}

void SpaceScene::ProcessInput(const InputManager& input)
{
	/*if (input.IsKeyPressed(GLFW_KEY_ENTER))
	{
		std::cout << "Démarrage du jeu !" << std::endl;
		sceneManager->ChangeScene(SPACE);
	}*/

	if (terminiActived)
	{
		termini.ProcessInput(&input);
	}
	else
	{
		if (input.IsKeyPressed(GLFW_KEY_W))
		{
			cam.ProcessPositionOffset(FORWARD, 0.01f);
		}
		if (input.IsKeyPressed(GLFW_KEY_A))
		{
			cam.ProcessPositionOffset(LEFT, 0.01f);
		}
		if (input.IsKeyPressed(GLFW_KEY_D))
		{
			cam.ProcessPositionOffset(RIGHT, 0.01f);
		}
		if (input.IsKeyPressed(GLFW_KEY_S))
		{
			cam.ProcessPositionOffset(BACKWARD, 0.01f);
		}
		if (input.IsKeyPressed(GLFW_KEY_SPACE))
		{
			cam.ProcessPositionOffset(UP, 0.01f);
		}
		if (input.IsKeyPressed(GLFW_KEY_LEFT_ALT))
		{
			cam.ProcessPositionOffset(DOWN, 0.01f);
		}

		if (input.IsKeyPressed(GLFW_KEY_E))
		{
			cam.ProcessRollOffset(-0.01f);
		}
		if (input.IsKeyPressed(GLFW_KEY_Q))
		{
			cam.ProcessRollOffset(0.01f);
		}
	}

	if (input.IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && input.IsKeyPressed(GLFW_KEY_T))
	{
		terminiActived = !terminiActived;
	}

	

	double x_off, y_off;
	input.GetCursorOffset(&x_off, &y_off);

	cam.ProcessYawPitchOffset((float)atan(x_off * 0.001),
							 (float)atan(y_off * 0.001));
	
}

void SpaceScene::Update(float deltaTime)
{
	earth.UpdateModelMatrix();
}

void SpaceScene::Render()
{
	setUniformEarth();
	earth.Bind();
	earth.Draw();
	
	if (terminiActived)
	{
		termini.Draw();
	}
}

void SpaceScene::Destroy()
{
	std::cout << "SpaceScene détruite !" << std::endl;
	glDeleteProgram(simple_shader.ID);
	glDeleteProgram(glyphShader.ID);
}

void SpaceScene::setUniformEarth()
{
	glUseProgram(simple_shader.ID);
	Shader::setVec3(simple_shader.ID, "viewPos", cam.GetPosition());
	Shader::setVec3(simple_shader.ID, "light_pos", sunlight.GetPosition());
	Shader::setVec3(simple_shader.ID, "light_color", sunlight.GetColor());
	Shader::setFloat(simple_shader.ID, "ambiant", sunlight.GetAmbiant());

	Shader::setMat4(simple_shader.ID, "view", cam.GetViewMatrix());
	Shader::setMat4(simple_shader.ID, "projection", &projMatrix);

	Shader::setMat4(earth.GetShader(), "model", earth.GetModelMatrix());
}
