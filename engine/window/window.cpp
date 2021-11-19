#include "pch/wavepch.h"
#include "imgui/imgui_context.h"
#include "event/event.h"
#include "event/event_handler.h"
#include "window.h"

namespace Wave
{
	void Window::Create(int const& width, int const& height, const char* title)
	{
		TRACE("Initializing window: {}", title);
		m_Width = width;
		m_Height = height;
		m_Title = title;

		// Window hints need to be set before the creation of the window. They function as additional arguments to glfwCreateWindow.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WAVE_OPENGL_VERSION_MAJ);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WAVE_OPENGL_VERSION_MIN);
		m_GlfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!m_GlfwWindow)
		{
			CRITICAL("Failed to create GLFWindow");
		}
		glfwSetWindowUserPointer(m_GlfwWindow, this);
		glfwMakeContextCurrent(m_GlfwWindow);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			CRITICAL("Failed to initialize OpengGL context");
		}

		TRACE("Checking system OpenGL version");
		GLint glMaj, glMin;
		glGetIntegerv(GL_MAJOR_VERSION, (&glMaj));
		glGetIntegerv(GL_MINOR_VERSION, (&glMin));
		TRACE("System OpenGL version : [{}.{}]", glMaj, glMin);
		TRACE("Wave OpenGL version : [{}.{}]", WAVE_OPENGL_VERSION_MAJ, WAVE_OPENGL_VERSION_MIN);
		if (glMaj < WAVE_OPENGL_VERSION_MAJ && glMin < WAVE_OPENGL_VERSION_MIN)
		{
			CRITICAL("System doesn't meet the OpenGL version criteria");
		}

		glEnable(GL_DEPTH_TEST);

		SetupCallbacks();

		//m_EventHandler = std::make_unique<EventHandler>();
	}

	void Window::Begin()
	{
		glfwMakeContextCurrent(m_GlfwWindow);
		Clear();
	}

	void Window::End()
	{
		glfwSwapBuffers(m_GlfwWindow);
	}


	void Window::Destroy()
	{
		// Shutdown glfw
		glfwDestroyWindow(m_GlfwWindow);
		glfwTerminate();
	}

	/*void Window::Run()
	{
		while (!glfwWindowShouldClose(m_GlfwWindow))
		{
			UpdateTime();

			m_EventHandler->Update(m_EventBuffer);

			m_ImGuiContext->Update();
			Update(m_DeltaTime);

			Clear();
			Render(m_DeltaTime);
			m_ImGuiContext->Render();

			m_EventHandler->Flush();
			glfwSwapBuffers(m_GlfwWindow);
			glfwPollEvents();
		}
	}*/


	/*EventHandler& Window::GetEventHandler() {
		return *m_EventHandler; 
	}*/

	void Window::Clear()
	{
		glm::vec4 clear_color = glm::vec4(0.002f, 0.002f, 0.002f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	template<typename T>
	void Window::TrimBuffer(std::queue<T>& buffer)
	{
		while (buffer.size() > m_MaxBufferSize)
		{
			buffer.pop();
		}
	}

#pragma region _____CALLBACKS
	void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_EventBuffer.emplace(std::make_unique<KeyEvent>(key, scancode, action, mods));
		TrimBuffer(m_EventBuffer);
	}

	void Window::MouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		m_EventBuffer.emplace(std::make_unique<MouseEvent>(button, action, mods));
		TrimBuffer(m_EventBuffer);
	}

	void Window::CursorCallback(GLFWwindow* window, double xPos, double yPos)
	{
		m_EventBuffer.emplace(std::make_unique<CursorEvent>(xPos, yPos));
		TrimBuffer(m_EventBuffer);
	}

	void Window::CursorEnterCallback(GLFWwindow* window, int entered)
	{
		m_EventBuffer.emplace(std::make_unique<CursorEnterEvent>(entered));
		TrimBuffer(m_EventBuffer);
	}

	void Window::ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
	{
		m_EventBuffer.emplace(std::make_unique<ScrollEvent>(x_offset, y_offset));
		TrimBuffer(m_EventBuffer);
	}

	void Window::WindowCloseCallback(GLFWwindow* window)
	{
		glfwSetWindowShouldClose(m_GlfwWindow, true);
	}

	void Window::WindowFocusCallback(GLFWwindow* window, int focused)
	{
		m_EventBuffer.emplace(std::make_unique<WindowFocusEvent>(focused));
		TrimBuffer(m_EventBuffer);
	}

	void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{

	}

	void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::ErrorCallback(int error, const char* description)
	{
		ERROR(description);
	}

	void Window::SetupCallbacks()
	{
		// Key callback
		auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods);
		};
		glfwSetKeyCallback(m_GlfwWindow, keyCallback);

		// Mouse callback
		auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->MouseCallback(window, button, action, mods);
		};
		glfwSetMouseButtonCallback(m_GlfwWindow, mouseCallback);

		// Cursor callback
		auto cursorCallback = [](GLFWwindow* window, double xpos, double ypos) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->CursorCallback(window, xpos, ypos);
		};
		glfwSetCursorPosCallback(m_GlfwWindow, cursorCallback);

		// Cursor enter callback
		auto cursorEnterCallback = [](GLFWwindow* window, int entered) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->CursorEnterCallback(window, entered);
		};
		glfwSetCursorEnterCallback(m_GlfwWindow, cursorEnterCallback);

		// Scroll callback
		auto scrollCallback = [](GLFWwindow* window, double xoffset, double yoffset) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->ScrollCallback(window, xoffset, yoffset);
		};
		glfwSetScrollCallback(m_GlfwWindow, scrollCallback);

		// Window close callback
		auto windowcloseCallback = [](GLFWwindow* window) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->WindowCloseCallback(window);
		};
		glfwSetWindowCloseCallback(m_GlfwWindow, windowcloseCallback);

		// Window focus callback
		auto windowfocusCallback = [](GLFWwindow* window, int focused) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->WindowFocusCallback(window, focused);
		};
		glfwSetWindowFocusCallback(m_GlfwWindow, windowfocusCallback);

		// Window size callback
		auto windowsizeCallback = [](GLFWwindow* window, int width, int height) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->WindowSizeCallback(window, width, height);
		};
		glfwSetWindowSizeCallback(m_GlfwWindow, windowsizeCallback);

		// Framebuffer callback
		auto framebufferCallback = [](GLFWwindow* window, int width, int height) {
			static_cast<Wave::Window*>(glfwGetWindowUserPointer(window))->FramebufferSizeCallback(window, width, height);
		};
		glfwSetFramebufferSizeCallback(m_GlfwWindow, framebufferCallback);

		// Error callback
		glfwSetErrorCallback(Window::ErrorCallback);
	}
#pragma endregion
}