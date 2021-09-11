#pragma once

#include "window.h"

namespace Wave
{
	class WindowGlfw : Window
	{
	public:
		WindowGlfw() = delete;
		WindowGlfw(int width, int height, const char* title);
		~WindowGlfw();
	public:
		void Run() override;
		void* GetNativeWindow() override { return mGlfwWindow; }
	protected:
		virtual void Update(float delta_time) = 0;
		virtual void Render(float delta_time) = 0;
	private:
		void Clear();
		void UpdateTime();
	protected:
		float mDeltaTime = 0;
		InputHandler mInputHandler;
	private:
		GLFWwindow* mGlfwWindow = nullptr;
		float mCurrentTime = 0, mPreviousTime = 0;
	private:
		std::unique_ptr<ImGuiContext> mImGuiContext;
	private:
		const uint mBufferSize = 16;
		std::queue<std::unique_ptr<InputHandler::InputEvent>> mEventBuffer;
	private:
		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int modes);
		void MouseCallback(GLFWwindow* window, int button, int action, int mods);
		void CursorCallback(GLFWwindow* window, double xpos, double ypos);
		void CursorEnterCallback(GLFWwindow* window, int entered);
		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		void WindowCloseCallback(GLFWwindow* window);
		void WindowFocusCallback(GLFWwindow* window, int focused);
		void WindowSizeCallback(GLFWwindow* window, int width, int height);
		void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void ErrorCallback(int error, const char* description);
		void SetupCallbacks();
	};
}