#pragma once

#include "window/window_glfw.h"

namespace Sandbox
{
	class App : public Wave::WindowGlfw
	{
	public:
		App() = delete;
		App(int width, int height, const char* title);
	protected:
		void Update(float deltaTime) override;
		void Render(float deltaTime) override;
	private:
		Wave::Camera* camera;
		Wave::Shader shader;
		Wave::VertexBuffer vb;
		Wave::Light light;

	};
}
