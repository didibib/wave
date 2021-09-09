#include "wavepch.h"
#include "input.h"
#include "imgui_context.h"
#include "opengl_buffers.h"
#include "window_glfw.h"

namespace wave
{
	window_glfw::window_glfw(int width, int height, const char* title) : window(width, height, title)
	{
		log::init();
		TRACE("Initializing window: {}", title);
		glfwInit();
		// Window hints need to be set before the creation of the window. They function as additional arguments to glfwCreateWindow.
		TRACE("[OPENGL VERSION:{}][MAX:{}][MIN:{}]", WAVE_OPENGL_VERSION, WAVE_OPENGL_VERSION_MAJ, WAVE_OPENGL_VERSION_MIN);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, WAVE_OPENGL_VERSION_MAJ);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, WAVE_OPENGL_VERSION_MIN);
		m_glfw_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!m_glfw_window)
		{
			CRITICAL("Failed to create GLFWindow");
		}
		glfwSetWindowUserPointer(m_glfw_window, this);
		glfwMakeContextCurrent(m_glfw_window);
		
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			CRITICAL("Failed to initialize OpengGL context");
		}
		setup_callbacks();

		m_imgui_context = std::make_unique<imgui_context>();
		m_imgui_context->init((window*)this);
	}

	window_glfw::~window_glfw()
	{
		m_imgui_context->shutdown();
		// Shutdown glfw
		glfwDestroyWindow(m_glfw_window);
		glfwTerminate();
		// Shutdown logger
		log::shutdown();
	}

	void window_glfw::run()
	{
		while (!glfwWindowShouldClose(m_glfw_window))
		{
			glfwPollEvents();
			update_time();

			m_input_handler.update(m_event_buffer);

			clear();

			m_imgui_context->update();
			update(m_delta_time);

			render(m_delta_time);
			m_imgui_context->render();

			glfwSwapBuffers(m_glfw_window);
		}
	}

	void window_glfw::clear()
	{
		glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void window_glfw::update_time()
	{
		m_current_time = glfwGetTime();
		m_delta_time = m_current_time - m_previous_time;
		m_previous_time = m_current_time;
	}

#pragma region _____CALLBACKS
	void window_glfw::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		m_event_buffer.emplace(std::make_unique<input_handler::key_event>(key, scancode, action, mods));
	}

	void window_glfw::mouse_callback(GLFWwindow* window, int button, int action, int mods)
	{
		m_event_buffer.emplace(std::make_unique<input_handler::mouse_event>(button, action, mods));
	}

	void window_glfw::cursor_callback(GLFWwindow* window, double xPos, double yPos)
	{
		m_event_buffer.emplace(std::make_unique<input_handler::cursor_event>(xPos, yPos));
	}

	void window_glfw::cursor_enter_callback(GLFWwindow* window, int entered)
	{
		m_input_handler.get_cursor().set_state(entered);
	}

	void window_glfw::scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
	{
		m_event_buffer.emplace(std::make_unique<input_handler::scroll_event>(x_offset, y_offset));
	}

	void window_glfw::window_close_callback(GLFWwindow* window)
	{
		glfwSetWindowShouldClose(m_glfw_window, true);
	}

	void window_glfw::window_focus_callback(GLFWwindow* window, int focused)
	{
		m_input_handler.get_cursor().set_state(focused);
	}

	void window_glfw::window_size_callback(GLFWwindow* window, int width, int height)
	{
		
	}

	void window_glfw::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void window_glfw::error_callback(int error, const char* description)
	{
		ERROR(description);
	}

	void window_glfw::setup_callbacks()
	{
		// Key callback
		auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->key_callback(window, key, scancode, action, mods);
		};
		glfwSetKeyCallback(m_glfw_window, keyCallback);

		// Mouse callback
		auto mouseCallback = [](GLFWwindow* window, int button, int action, int mods) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->mouse_callback(window, button, action, mods);
		};
		glfwSetMouseButtonCallback(m_glfw_window, mouseCallback);

		// Cursor callback
		auto cursorCallback = [](GLFWwindow* window, double xpos, double ypos) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->cursor_callback(window, xpos, ypos);
		};
		glfwSetCursorPosCallback(m_glfw_window, cursorCallback);

		// Cursor enter callback
		auto cursorEnterCallback = [](GLFWwindow* window, int entered) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->cursor_enter_callback(window, entered);
		};
		glfwSetCursorEnterCallback(m_glfw_window, cursorEnterCallback);

		// Scroll callback
		auto scrollCallback = [](GLFWwindow* window, double xoffset, double yoffset) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->scroll_callback(window, xoffset, yoffset);
		};
		glfwSetScrollCallback(m_glfw_window, scrollCallback);

		// Window close callback
		auto windowcloseCallback = [](GLFWwindow* window) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->window_close_callback(window);
		};
		glfwSetWindowCloseCallback(m_glfw_window, windowcloseCallback);

		// Window focus callback
		auto windowfocusCallback = [](GLFWwindow* window, int focused) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->window_focus_callback(window, focused);
		};
		glfwSetWindowFocusCallback(m_glfw_window, windowfocusCallback);

		// Window size callback
		auto windowsizeCallback = [](GLFWwindow* window, int width, int height) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->window_size_callback(window, width, height);
		};
		glfwSetWindowSizeCallback(m_glfw_window, windowsizeCallback);

		// Framebuffer callback
		auto framebufferCallback = [](GLFWwindow* window, int width, int height) {
			static_cast<wave::window_glfw*>(glfwGetWindowUserPointer(window))->framebuffer_size_callback(window, width, height);
		};
		glfwSetFramebufferSizeCallback(m_glfw_window, framebufferCallback);

		// Error callback
		glfwSetErrorCallback(window_glfw::error_callback);
	}
#pragma endregion
}