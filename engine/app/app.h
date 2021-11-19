#pragma once

namespace Wave
{
	class Window;

	class App
	{
	public:
		App() = default;
		~App() = default;
		virtual void Init() = 0;
		virtual void Update(const float&) = 0;

	protected:
		std::vector<std::unique_ptr<Window>> m_Windows;

	};
}