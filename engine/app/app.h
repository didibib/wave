#pragma once

namespace Wave
{
	enum class AppState { Running, Stopped };

	class App
	{
	public:
		App() = default;
		~App() = default;
		virtual void Init() = 0;
		virtual AppState Update(const float&) = 0;
		virtual void Shutdown() = 0;
	};
}