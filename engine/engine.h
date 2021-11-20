#pragma once

namespace Wave
{
	class App;
	class Engine;
	class WindowParams;
	class WindowSubsystem;

	class Engine
	{
	public:
		static Engine& GetInstance()
		{
			// Guaranteed to be destroyed.
			// Instantiated on first use.
			static Engine instance;
			return instance;
		}
		void Init();
		void StartUp(App*, WindowParams);
		void Run();
		void Shutdown();
		// Singleton requirements
		Engine(Engine const&) = delete;
		void operator=(Engine const&) = delete;
	protected:
		Engine() = default;
	private:
		App* m_App;
		WindowSubsystem* m_WindowSubsystem;
	};
}