#pragma once

namespace Wave
{
	class Window
	{
	public:
		Window(int width, int height, const char* title) {
			Log::Init();
			m_Width = width;
			m_Height = height;
			m_Title = title;
		}
		~Window()
		{
			Log::Shutdown();
		}
	public:
		virtual void Run() = 0;
		virtual void* GetNativeWindow() = 0;
	public:
		int GetWidth() { return m_Width; }
		int GetHeight() { return m_Height; }
		std::string GetTitle() { return m_Title; }
	protected:
		int m_Width;
		int m_Height;
		std::string m_Title;
	};
}