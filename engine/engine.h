#pragma once

namespace Wave
{
	class App;

	struct EngineSettings
	{
		int Width;
		int Height;
		const char* Title;
	};

	class Engine : public Singleton<Engine>
	{
	public:
		Engine() = default;
		~Engine() = default;
		void StartUp(App& app, EngineSettings& settings);
		void Run();
		void Shutdown();
	public:
		Engine(Engine const&) = delete;
		void operator=(Engine const&) = delete;

	private:
		std::unique_ptr<Window> m_Window;
	};
}