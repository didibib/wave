#pragma once

#include "window/window.h"

namespace Wave
{
	class ImGuiContext
	{
	public:
		void Init(Window* window);
		void Shutdown();

		void Update();
		void Render();
	};
}