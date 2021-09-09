#pragma once

#include "window.h"

namespace wave
{
	class imgui_context
	{
	public:
		void init(window* window);
		void shutdown();

		void update();
		void render();
	};
}