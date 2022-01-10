#pragma once 

namespace Wave
{
	class Window;

	class WindowParams
	{
		friend Window;
	public:
		void SetWidth(int width)
		{
			m_Width = width;
		}
		void SetHeight(int height)
		{
			m_Height = height;
		}
		void SetTitle(const char* title)
		{
			m_Title = title;
		}
		void SetMonitor(GLFWmonitor* monitor)
		{
			m_Monitor = monitor;
		}
		void SetSharedContext(GLFWwindow* share)
		{
			m_Share = share;
		}

	private:
		int m_Width = 0, m_Height = 0;
		const char* m_Title = "";
		GLFWmonitor* m_Monitor = nullptr;
		GLFWwindow* m_Share = nullptr;
	};
}