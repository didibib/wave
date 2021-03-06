#include "pch/editorpch.h"
#include "editor_app.h"

namespace Editor
{
	void EditorApp::Init()
	{
		glEnable(GL_DEPTH_TEST);

		auto& tm = Wave::TextureManager::GetInstance();

		std::string texDir = Wave::Asset::GetDirectory() + "/textures/";
		tm.Load(texDir + "container_diffuse.png", Wave::TextureType::Diffuse, "c_diff");
		tm.Load(texDir + "container_specular.png", Wave::TextureType::Diffuse, "c_spec");
		tm.Load(texDir + "matrix.jpg", Wave::TextureType::Diffuse, "matrix");

		auto shaderDir = Wave::Asset::GetDirectory() + "/shaders/";
		m_Shader.Load(shaderDir + "phong");
		m_Shader.Begin();
		/*m_Shader.SetInt("u_Material.diffuse", 0);
		m_Shader.SetInt("u_Material.specular", 1);
		m_Shader.SetInt("u_Material.emission", 2);*/
		m_Shader.End();

		auto modelDir = Wave::Asset::GetDirectory() + "/models";
		//m_Model.Load(modelDir + "/backpack/backpack.obj");
		m_Vb.Create(Wave::Cube::GetVertices());

		m_Camera = std::make_unique<Wave::Camera>(60, 800, 600, 0.1f, 1000.f);
		m_Camera->SetPos({ 0, 0, 3 });
		m_Light.SetPos({ 0.f, 3.f, 0.f });
	}

	Wave::Result EditorApp::Update(const float& deltaTime)
	{
		/*Wave::EventHandler& inputHandler = GetEventHandler();
		if (inputHandler.IsMouseRepeat(GLFW_MOUSE_BUTTON_2))
		{
			if (inputHandler.IsKeyRepeat(GLFW_KEY_W)) m_Camera->Move(Wave::Direction::Forward, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_S)) m_Camera->Move(Wave::Direction::Backward, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_A)) m_Camera->Move(Wave::Direction::Left, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_D)) m_Camera->Move(Wave::Direction::Right, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_SPACE)) m_Camera->Move(Wave::Direction::Up, deltaTime);
			if (inputHandler.IsKeyRepeat(GLFW_KEY_LEFT_CONTROL)) m_Camera->Move(Wave::Direction::Down, deltaTime);
			auto offset = inputHandler.GetCursor().GetOffset();
			m_Camera->Cursor(offset.x, offset.y);
		}*/

		auto ws = Wave::Locator::GetInstance().Get<Wave::WindowSubsystem>();
		auto w = ws->Get();

		w->Begin();
		Render(deltaTime);
		w->End();

		/*auto w2 = ws->Get(1);
		w2->Begin();
		Render(deltaTime);
		w2->End();*/

		return Wave::Result::Running;
	}

	void EditorApp::Shutdown()
	{
	}

	void EditorApp::Render(const float& deltaTime)
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

		// Positions of the point lights
		glm::vec3 pointLightPositions[] = {
			glm::vec3(0.7f,  0.2f,  2.0f),
			glm::vec3(2.3f, -3.3f, -4.0f),
			glm::vec3(-4.0f,  2.0f, -12.0f),
			glm::vec3(0.0f,  0.0f, -3.0f)
		};

		m_Shader.Begin();
		
		m_Shader.SetFloat("u_Material.shininess", 32.0f);
		
		// Directional light
		/*m_Shader.SetVec3("u_DirLight.direction", -0.2f, -1.0f, -0.3f);
		m_Shader.SetVec3("u_DirLight.ambient", 0.05f, 0.05f, 0.05f);
		m_Shader.SetVec3("u_DirLight.diffuse", 0.4f, 0.4f, 0.4f);
		m_Shader.SetVec3("u_DirLight.specular", 0.5f, 0.5f, 0.5f);*/

		// Point lights
		for (GLuint i = 0; i < 4; i++)
		{
			std::string number = std::to_string(i);
			m_Shader.SetVec3(("u_PointLights[" + number + "].position").c_str(), pointLightPositions[i]);
			m_Shader.SetVec3(("u_PointLights[" + number + "].ambient").c_str(), 0.5f, 0.5f, 0.5f);
			m_Shader.SetVec3(("u_PointLights[" + number + "].diffuse").c_str(), 0.8f, 0.8f, 0.8f);
			m_Shader.SetVec3(("u_PointLights[" + number + "].specular").c_str(), 1.0f, 1.0f, 1.0f);
			m_Shader.SetFloat(("u_PointLights[" + number + "].constant").c_str(), 1.0f);
			m_Shader.SetFloat(("u_PointLights[" + number + "].linear").c_str(), 0.09f);
			m_Shader.SetFloat(("u_PointLights[" + number + "].quadratic").c_str(), 0.032f);
		}

		// Spot light
		m_Shader.SetVec3("u_SpotLight.position", m_Camera->GetPos());
		m_Shader.SetVec3("u_SpotLight.direction", m_Camera->GetForward());
		m_Shader.SetVec3("u_SpotLight.ambient", 0.f, 0.f, 0.f);
		m_Shader.SetVec3("u_SpotLight.diffuse", 1.0f, 1.0f, 1.0f);
		m_Shader.SetVec3("u_SpotLight.specular", 1.0f, 1.0f, 1.0f);
		m_Shader.SetFloat("u_SpotLight.constant", 1.0f);
		m_Shader.SetFloat("u_SpotLight.linear", 0.09);
		m_Shader.SetFloat("u_SpotLight.quadratic", 0.032);
		m_Shader.SetFloat("u_SpotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_Shader.SetFloat("u_SpotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		// Set matrices
		m_Shader.SetMat4("u_Projection", m_Camera->GetProjMatrix());
		m_Shader.SetMat4("u_View", m_Camera->GetViewMatrix());
		m_Shader.SetVec3("u_ViewPosition", m_Camera->GetPos());

		//m_Model.Draw(m_Shader);

		// Render boxes
		auto& tm = Wave::TextureManager::GetInstance();

		tm.Bind("c_diff", GL_TEXTURE0);
		tm.Bind("c_spec", GL_TEXTURE1);
		tm.Bind("matrix", GL_TEXTURE2);

		for (unsigned int i = 0; i < 10; i++)
		{
			// Calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			glm::mat4 normalMatrix = glm::transpose(glm::inverse(model));
						
			m_Shader.SetMat4("u_Model", model);
			m_Shader.SetMat4("u_NormalMatrix", normalMatrix);

			m_Vb.Bind();
			m_Vb.Draw();
			m_Vb.Unbind();
		}
		m_Shader.End();
	}
}