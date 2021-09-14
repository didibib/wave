#include "pch/sandboxpch.h"
#include "app.h"

namespace Sandbox
{
	App::App(int width, int height, const char* weather) : Wave::WindowGlfw(width, height, weather)
	{
		auto& tm = Wave::TextureManager::GetInstance();
		texId1 = *tm.Load("brick_wall.jpg");
		texId2 = *tm.Load("awesomeface.png");

		shader.Load("phong");
		shader.Begin();
		shader.SetInt("texture0", 0);
		shader.SetInt("texture1", 1);
		shader.End();

		vb.Create(Wave::Cube::GetVertices());
		camera = new Wave::Camera(60, Window::GetWidth(), Window::GetHeight(), 0.1f, 1000.f);
		camera->SetPos({ 0, 0, 3 });
		light.SetPos({ 0.f, 3.f, 0.f });
	}
	void App::Update(float deltaTime)
	{
		auto inputHandler = GetInputHandler();
		if (inputHandler.IsMouseRepeat(GLFW_MOUSE_BUTTON_2))
		{
			if (inputHandler.IsKeyRepeat(GLFW_KEY_W)) camera->Move(Wave::Direction::Forward, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_S)) camera->Move(Wave::Direction::Backward, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_A)) camera->Move(Wave::Direction::Left, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_D)) camera->Move(Wave::Direction::Right, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_SPACE)) camera->Move(Wave::Direction::Up, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_LEFT_CONTROL)) camera->Move(Wave::Direction::Down, deltaTime);
			auto offset = inputHandler.GetCursor().GetOffset();
			camera->Cursor(offset.x, offset.y);
		}
	}

	void App::Render(float deltaTime)
	{
		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		auto& tm = Wave::TextureManager::GetInstance();
		
		glActiveTexture(GL_TEXTURE0);
		tm.Bind(texId1);
		glActiveTexture(GL_TEXTURE1);
		tm.Bind(texId2);

		shader.Begin();
		shader.SetMat4("projection", camera->GetProjMatrix());
		shader.SetMat4("view", camera->GetViewMatrix());
		shader.SetVec3("objectColor", 1.0f, 0.5f, 0.31f);
		shader.SetVec3("lightColor", light.GetColor());

		float lightX = 2.0f * sin(glfwGetTime());
		float lightY = -0.3f;
		float lightZ = 1.5f * cos(glfwGetTime());
		light.SetPos(lightX, lightY, lightZ);
		shader.SetVec3("lightPosition", light.GetPos());
		shader.SetFloat("lightStrength", light.GetStrength());
		shader.SetVec3("viewPosition", camera->GetPos());

		// Render boxes
		vb.Bind();
		for (unsigned int i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 normalMatrix = glm::transpose(glm::inverse(model));
						
			shader.SetMat4("model", model);
			shader.SetMat4("normalMatrix", normalMatrix);

			vb.Draw();
		}
		shader.End();
	}
}