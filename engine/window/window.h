#pragma once

#include "event/event.h"

namespace Wave
{
	class EventHandler;

	class Window
	{
	public:
		void Create(int const& width, int const& height, const char* title);
		void Begin();
		void End();
		void Destroy();
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		std::string GetTitle() { return m_Title; }
		void* GetNativeWindow() { return m_GlfwWindow; }
		//EventHandler& GetEventHandler();
	private:
		int m_Width;
		int m_Height;
		std::string m_Title;
		void Clear();
		GLFWwindow* m_GlfwWindow = nullptr;
		//std::unique_ptr<EventHandler> m_EventHandler;
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