#pragma once

#include "window.h"

namespace wave
{
	class window_glfw : window
	{
	public:
		window_glfw() = delete;
		window_glfw(int width, int height, const char* title);
		~window_glfw();
	public:
		void run() override;
		void* get_native_window() override { return m_glfw_window; }
	protected:
		virtual void update(float delta_time) = 0;
		virtual void render(float delta_time) = 0;
	protected:
		float m_delta_time = 0;
		input_handler m_input_handler;
	private:
		GLFWwindow* m_glfw_window = nullptr;
		float m_current_time = 0, m_previous_time = 0;
	private:
		std::unique_ptr<imgui_context> m_imgui_context;
	private:
		const uint m_buffer_size = 16;
		std::queue<std::unique_ptr<input_handler::input_event>> m_event_buffer;
	private:
		void clear();
		void update_time();
	private:
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int modes);
		void mouse_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_callback(GLFWwindow* window, double xpos, double ypos);
		void cursor_enter_callback(GLFWwindow* window, int entered);
		void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		void window_close_callback(GLFWwindow* window);
		void window_focus_callback(GLFWwindow* window, int focused);
		void window_size_callback(GLFWwindow* window, int width, int height);
		void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void error_callback(int error, const char* description);
		void setup_callbacks();
	};
}