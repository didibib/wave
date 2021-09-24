#pragma once

#include "window.h"

namespace Wave
{
	class WindowGlfw : public Window
	{
	public:
		WindowGlfw() = delete;
		WindowGlfw(int const& width, int const& height, const char* title);
		~WindowGlfw();
	public:
		void Run() override;
		void* GetNativeWindow() override { return m_GlfwWindow; }
		float GetDeltaTime() { return m_DeltaTime; }
		EventHandler GetInputHandler() { return m_InputHandler; }
	protected:
		virtual void Update(float const& deltaTime) = 0;
		virtual void Render(float const& deltaTime) = 0;
	private:
		void Clear();
		void UpdateTime();
	private:
		float m_DeltaTime = 0;
		float m_CurrentTime = 0, m_PreviousTime = 0;
		GLFWwindow* m_GlfwWindow = nullptr;
		EventHandler m_InputHandler;
	private:
		std::unique_ptr<ImGuiContext> m_ImGuiContext;
	private:
		const uint m_MaxBufferSize = 16;
		std::queue<std::unique_ptr<Event>> m_EventBuffer;
		template<typename T> void TrimBuffer(std::queue<T>& buffer);
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