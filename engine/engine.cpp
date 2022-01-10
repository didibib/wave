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
	m_WindowSubsystem = locator.Register<WindowSubsystem>();
}

void Wave::Engine::StartUp(App* app, WindowParams params)
{
	// Add main window
	m_WindowSubsystem->AddNewWindow(params);

	m_App = std::move(app);
	m_App->Init();
}

void Wave::Engine::Run()
{
	Result state = Result::Running;
	while (state == Result::Running)
	{
		static float currentTime = 0.0f;
		static float previousTime = 0.0f;

		currentTime = glfwGetTime();
		float deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		state = m_WindowSubsystem->Update(deltaTime);
		if (state != Result::Running) break;

		state = m_App->Update(deltaTime);
		if (state != Result::Running) break;
	}
}

void Wave::Engine::Shutdown()
{
	m_App->Shutdown();
	Logger::Shutdown();
	glfwTerminate();
}
