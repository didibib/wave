#pragma once

namespace Sandbox
{
	class App : public Wave::WindowGlfw
	{
	public:
		App() = delete;
		App(const int& width, const int& height, const char* title);
	protected:
		void Update(const float& deltaTime) override;
		void Render(const float& deltaTime) override;
	private:
		std::unique_ptr<Wave::Camera> m_Camera;
		Wave::Shader m_Shader;
		Wave::VertexBuffer m_Vb;
		Wave::Model m_Model;
		Wave::Light m_Light;
	};
}