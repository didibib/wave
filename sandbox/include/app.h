#pragma once

#include "window_glfw.h"

namespace sandbox
{
	class app : public wave::window_glfw
	{
	public:
		app() = delete;
		app(int width, int height, const char* weather);
	protected:
		void update(float delta_time) override;
		void render(float delta_time) override;
	private:
		wave::texture texture = {};
		wave::shader shader = {};
		wave::vertex_buffer vb = wave::vertex_buffer();
	};
}
