#include "pch/wavepch.h"
#include "events/input.h"
#include "context/imgui_context.h"
#include "window_glfw.h"

namespace Wave
{
	WindowGlfw::WindowGlfw(int width, int height, const char* title) : Window(width, height, title)
	{
		TRACE("Initializing window: {}", title);
		glfwInit();
		// Window hints need to be set before the creation of the window. They function as additional arguments to glfwCreateWindow.
		TRACE("[OPENGL VERSION:{}][MAX:{}][MIN:{}]", WAVE_OPENGL_VERSION, WAVE_OPENGL_VERSION_MAJ, WAVE_OPENGL_VERSION_MIN);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WAVE_OPENGL_VERSION_MAJ);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WAVE_OPENGL_VERSION_MIN);
		mGlfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!mGlfwWindow)
		{
			CRITICAL("Failed to create GLFWindow");
		}
		glfwSetWindowUserPointer(mGlfwWindow, this);
		glfwMakeContextCurrent(mGlfwWindow);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			CRITICAL("Failed to initialize OpengGL context");
		}
		SetupCallbacks();

		mImGuiContext = std::make_unique<ImGuiContext>();
		mImGuiContext->Init((Window*)this);
	}

	WindowGlfw::~WindowGlfw()
	{
		mImGuiContext->Shutdown();
		// Shutdown glfw
		glfwDestroyWindow(mGlfwWindow);
		glfwTerminate();
	}

	void WindowGlfw::Run()
	{
		while (!glfwWindowShouldClose(mGlfwWindow))
		{
			glfwPollEvents();
			UpdateTime();

			mInputHandler.Update(mEventBuffer);

			Clear();

			Update(mDeltaTime);
			mImGuiContext->Update();

			Render(mDeltaTime);
			mImGuiContext->Render();

			glfwSwapBuffers(mGlfwWindow);
		}
	}

	void WindowGlfw::Clear()
	{
		glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WindowGlfw::UpdateTime()
	{
		mCurrentTime = glfwGetTime();
		mDeltaTime = mCurrentTime - mPreviousTime;
		mPreviousTime = mCurrentTime;
	}

#pragma region _____CALLBACKS
	void WindowGlfw::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		mEventBuffer.emplace(std::make_unique<InputHandler::KeyEvent>(key, scancode, action, mods));
	}

	void WindowGlfw::MouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		mEventBuffer.emplace(std::make_unique<InputHandler::MouseEvent>(button, action, mods));
	}

	void WindowGlfw::CursorCallback(GLFWwindow* window, double xPos, double yPos)
	{
		mEventBuffer.emplace(std::make_unique<InputHandler::CursorEvent>(xPos, yPos));
	}

	void WindowGlfw::CursorEnterCallback(GLFWwindow* window, int entered)
	{
		mInputHandler.GetCursor().SetState(entered);
	}

	void WindowGlfw::ScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
	{
		mEventBuffer.emplace(std::make_unique<InputHandler::ScrollEvent>(x_offset, y_offset));
	}

	void WindowGlfw::WindowCloseCallback(GLFWwindow* window)
	{
		glfwSetWindowShouldClose(mGlfwWindow, true);
	}

	void WindowGlfw::WindowFocusCallback(GLFWwindow* window, int focused)
	{
		mInputHandler.GetCursor().SetState(focused);
	}

	void WindowGlfw::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		
	}

	void WindowGlfw::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void WindowGlfw::ErrorCallback(int error, const char* description)
	{
		ERROR(description);
	}

	void WindowGlfw::SetupCallbacks()
	{
		// Key callback
		auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->KeyCallback(window, key, scancode, action, mods);
		};
		glfwSetKeyCallback(mGlfwWindow, keyCallback);

		// Mouse callback
		auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->MouseCallback(window, button, action, mods);
		};
		glfwSetMouseButtonCallback(mGlfwWindow, mouseCallback);

		// Cursor callback
		auto cursorCallback = [](GLFWwindow* window, double xpos, double ypos) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->CursorCallback(window, xpos, ypos);
		};
		glfwSetCursorPosCallback(mGlfwWindow, cursorCallback);

		// Cursor enter callback
		auto cursorEnterCallback = [](GLFWwindow* window, int entered) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->CursorEnterCallback(window, entered);
		};
		glfwSetCursorEnterCallback(mGlfwWindow, cursorEnterCallback);

		// Scroll callback
		auto scrollCallback = [](GLFWwindow* window, double xoffset, double yoffset) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->ScrollCallback(window, xoffset, yoffset);
		};
		glfwSetScrollCallback(mGlfwWindow, scrollCallback);

		// Window close callback
		auto windowcloseCallback = [](GLFWwindow* window) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->WindowCloseCallback(window);
		};
		glfwSetWindowCloseCallback(mGlfwWindow, windowcloseCallback);

		// Window focus callback
		auto windowfocusCallback = [](GLFWwindow* window, int focused) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->WindowFocusCallback(window, focused);
		};
		glfwSetWindowFocusCallback(mGlfwWindow, windowfocusCallback);

		// Window size callback
		auto windowsizeCallback = [](GLFWwindow* window, int width, int height) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->WindowSizeCallback(window, width, height);
		};
		glfwSetWindowSizeCallback(mGlfwWindow, windowsizeCallback);

		// Framebuffer callback
		auto framebufferCallback = [](GLFWwindow* window, int width, int height) {
			static_cast<Wave::WindowGlfw*>(glfwGetWindowUserPointer(window))->FramebufferSizeCallback(window, width, height);
		};
		glfwSetFramebufferSizeCallback(mGlfwWindow, framebufferCallback);

		// Error callback
		glfwSetErrorCallback(WindowGlfw::ErrorCallback);
	}
#pragma endregion
}