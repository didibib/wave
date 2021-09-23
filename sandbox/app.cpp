#include "pch/sandboxpch.h"
#include "app.h"

namespace Sandbox
{
	App::App(int width, int height, const char* title) : Wave::WindowGlfw(width, height, title)
	{
		auto& tm = Wave::TextureManager::GetInstance();
		tm.Load("container_diffuse.png", "container_diffuse");
		tm.Load("container_specular.png", "container_specular");
		tm.Load("matrix.jpg", "matrix");

		shader.Load("phong");
		shader.Begin();
		shader.SetInt("material.diffuse", 0);
		shader.SetInt("material.specular", 1);
		shader.SetInt("material.emission", 2);
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
		
		tm.Bind("container_diffuse", GL_TEXTURE0);
		tm.Bind("container_specular", GL_TEXTURE1);
		tm.Bind("matrix", GL_TEXTURE2);

		shader.Begin();
		shader.SetMat4("u_Projection", camera->GetProjMatrix());
		shader.SetMat4("u_View", camera->GetViewMatrix());
		shader.SetVec3("u_ViewPosition", camera->GetPos());

		shader.SetVec3("u_Light.position", light.GetPos());
		shader.SetVec3("u_Light.ambient", light.GetAmbient());
		shader.SetVec3("u_Light.diffuse", light.GetDiffuse());
		shader.SetVec3("u_Light.specular", light.GetSpecular());
		shader.SetFloat("u_Light.strength", light.GetStrength());

		shader.SetFloat("u_Material.shininess", 32.0f);

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
						
			shader.SetMat4("u_Model", model);
			shader.SetMat4("u_NormalMatrix", normalMatrix);

			vb.Draw();
		}
		shader.End();
	}
}