#include "pch/wavepch.h"
#include "window/window.h"
#include "app/app.h"
#include "engine.h"

void Wave::Engine::StartUp(App& app, EngineSettings& settings)
{
	glfwInit();
	m_Window = std::make_unique<Window>();
	m_Window->Create(settings.Width, settings.Height, settings.Title);
	app.Init();
}

void Wave::Engine::Run()
{
	bool isRunning = true;
	while (isRunning)
	{
		static float currentTime = 0.0f;
		static float previousTime = 0.0f;
		float deltaTime = 0.0f;

		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		m_Window->Begin();

		m_Window->End();
	}
}

void Wave::Engine::Shutdown()
{
	m_Window->Destroy();
	glfwTerminate();
}
