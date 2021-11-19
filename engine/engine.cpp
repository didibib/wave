#include "pch/wavepch.h"
#include "window/window.h"
#include "app/app.h"
#include "engine.h"

void Wave::Engine::StartUp(std::unique_ptr<App> app)
{
	glfwInit();
	Logger::Init();
	m_App = std::move(app);
	m_App->Init();
}

void Wave::Engine::Run()
{
	AppState appState = AppState::Running;
	while (appState == AppState::Running)
	{
		static float currentTime = 0.0f;
		static float previousTime = 0.0f;
		float deltaTime = 0.0f;

		currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		appState = m_App->Update(deltaTime);
	}
}

void Wave::Engine::Shutdown()
{
	m_App->Shutdown();
	Logger::Shutdown();
	glfwTerminate();
}
