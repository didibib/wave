#include "pch/sandboxpch.h"
#include "app.h"

namespace sandbox
{
	App::App(int width, int height, const char* weather) : Wave::WindowGlfw(width, height, weather)
	{	
		auto& tm = Wave::TextureManager::GetInstance();
		temp1 = *tm.Load("brick_wall.jpg");
		temp2 = *tm.Load("ok.jpg");

		shader.Load("basic");
		shader.Begin();
		shader.SetInt("texture1", 0);
		shader.End();

		std::vector<Wave::Vertex> vert = {};
		vert.resize(4);
		vert[0].position =	glm::vec3(0.5f, 0.5f, 0.0f);		// top right
		vert[0].color =		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		vert[0].uv =		glm::vec2(1.0f, 1.0f);

		vert[1].position =	glm::vec3(0.5f, -0.5f, 0.0f);		// bottom right
		vert[1].color =		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		vert[1].uv =		glm::vec2(1.0f, 0.0f);

		vert[2].position =	glm::vec3(-0.5f, -0.5f, 0.0f);		// bottom left
		vert[2].color =		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		vert[2].uv =		glm::vec2(0.0f, 0.0f);

		vert[3].position =	glm::vec3(-0.5f, 0.5f, 0.0f);		// top left 
		vert[3].color =		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
		vert[3].uv =		glm::vec2(0.0f, 1.0f);

		std::vector<int> ind = {0, 1, 3, 1, 2, 3};

		vb.Create(vert, ind);
	}

	void App::Update(float delta_time)
	{

	}

	void App::Render(float delta_time)
	{
		// glActiveTexture(GL_TEXTURE0);
		auto& tm = Wave::TextureManager::GetInstance();
		tm.Bind(temp1);
		shader.Begin();
		vb.Draw();
		shader.End();
	}
}