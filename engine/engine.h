#pragma once

namespace Wave
{
	class App;

	class Engine : public Singleton<Engine>
	{
	public:
		Engine() = default;
		~Engine() = default;
		void StartUp(std::unique_ptr<App> app);
		void Run();
		void Shutdown();
	public:
		Engine(Engine const&) = delete;
		void operator=(Engine const&) = delete;
	private:
		std::unique_ptr<App> m_App;
	};
}