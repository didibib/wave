#pragma once

#include "window/window_glfw.h"

namespace sandbox
{
	class App : public Wave::WindowGlfw
	{
	public:
		App() = delete;
		App(int width, int height, const char* weather);
	protected:
		void Update(float delta_time) override;
		void Render(float delta_time) override;
	private:
		Wave::Shader shader;
		Wave::VertexBuffer vb;

		GLuint temp1, temp2;
	};
}
