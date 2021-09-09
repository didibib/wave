#include "sandboxpch.h"
#include "app.h"

namespace sandbox
{
	app::app(int width, int height, const char* weather) : wave::window_glfw(width, height, weather)
	{		
		texture.load("brick_wall.jpg");
		shader.load("basic");
		shader.begin();
		shader.set_int("texture1", 0);
		shader.end();

		std::vector<wave::vertex> vert = {};
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

		vb.create(vert, ind);
	}

	void app::update(float delta_time)
	{

	}

	void app::render(float delta_time)
	{
		// create transformations
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		glActiveTexture(GL_TEXTURE0);
		texture.bind();
		shader.begin();
		shader.set_mat4("transform", transform);
		vb.draw();
		shader.end();
	}
}