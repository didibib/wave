#include "pch/sandboxpch.h"
#include "app.h"

namespace sandbox
{
	App::App(int width, int height, const char* weather) : Wave::WindowGlfw(width, height, weather)
	{	
		auto& tm = Wave::TextureManager::GetInstance();
		tm.load("brick_wall.jpg");
		tm.load("ok.jpg");

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
		// create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		shader.Begin();
		vb.Draw();
		shader.End();

		// glActiveTexture(GL_TEXTURE0);
		/*texture.bind();
		shader.begin();
		shader.set_mat4("transform", transform);
		vb.draw();
		shader.end();*/
	}
}