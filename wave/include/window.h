#pragma once

namespace wave
{
	class window
	{
	public:
		window(int width, int height, const char* title) {
			m_width = width;
			m_height = height;
			m_title = title;
		}
	public:
		virtual void run() = 0;
		virtual void* get_native_window() = 0;
	public:
		int get_width() { return m_width; }
		int get_height() { return m_height; }
		std::string get_title() { return m_title; }
	protected:
		int m_width;
		int m_height;
		std::string m_title;
	};
}