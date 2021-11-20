#pragma once

#include "util/result.h"

namespace Wave
{
	class App
	{
	public:
		App() = default;
		~App() = default;
		virtual void Init() = 0;
		virtual Result Update(const float&) = 0;
		virtual void Shutdown() = 0;
	};
}