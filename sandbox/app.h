#pragma once

#include "window/window_glfw.h"

namespace Sandbox
{
	class App : public Wave::WindowGlfw
	{
	public:
		App() = delete;
		App(int const& width, int const& height, const char* title);
	protected:
		void Update(float const& deltaTime) override;
		void Render(float const& deltaTime) override;
	private:
		Wave::Camera* m_Camera;
		Wave::Shader m_Shader;
		Wave::VertexBuffer m_Vb;
		Wave::Light m_Light;

	};
}
