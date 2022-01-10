#pragma once

#include "event/event.h"
#include "util/result.h"
#include "subsystem.h"

namespace Wave
{
	class EventHandler;
	class WindowParams;
	class WindowSubsystem;

	class Window
	{
		friend WindowSubsystem;
	public:
		Window();
		~Window();
		void Init(WindowParams&);
		void Begin() const;
		void End() const;
		void Destroy()  const;
		bool ShouldClose() const;
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		std::string GetTitle() { return m_Title; }
		GLFWwindow* GetWindowPointer() { return m_GlfwWindow; }
		//EventHandler& GetEventHandler();
	private:
		void MakeContextCurrent() const;
		void Clear() const;
		void SwapBuffers() const;
		int m_Width;
		int m_Height;
		std::string m_Title;
		GLFWwindow* m_GlfwWindow = nullptr;
		//std::unique_ptr<EventHandler> m_EventHandler;
		const uint m_MaxBufferSize = 16;
		//std::queue<std::unique_ptr<Event>> m_EventBuffer;
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

	class WindowSubsystem : public Subsystem
	{
		// https://github.com/glfw/glfw/blob/master/examples/windows.c
	public:
		WindowSubsystem() = default;
		~WindowSubsystem()
		{
			for (auto& w : m_Windows)
			{
				delete w;
			}
		}

		void Init() override;
		Result Update(float const&) override;
		void Shutdown() override;

		void AddNewWindow(WindowParams&);
		Window* Get(int index = 0);

	private:
		bool HasOpenWindows();
		void PollEvents();
		std::vector<Window*> m_Windows;
	};
}