#include "pch/wavepch.h"
#include "engine.h"
#include "window/window.h"
#include "window/window_params.h"
#include "app/app.h"

void Wave::Engine::Init()
{
	glfwInit();
	Logger::Init();

	auto& locator = Locator::GetInstance();
	m_WindowSubsystem = locator.Register<WindowSubsystem>().get();
}

void Wave::Engine::StartUp(App* app, WindowParams params)
{
	m_WindowSubsystem->AddNewWindow(params);

	m_App = std::move(app);
	m_App->Init();
}

void Wave::Engine::Run()
{
	Result appState = Result::Running;
	while (appState == Result::Running)
	{
		static float currentTime = 0.0f;
		static float previousTime = 0.0f;

		currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		m_WindowSubsystem->Update(deltaTime);

		appState = m_App->Update(deltaTime);

		m_WindowSubsystem->End();
	}
}

void Wave::Engine::Shutdown()
{
	m_App->Shutdown();
	Logger::Shutdown();
	glfwTerminate();
}
