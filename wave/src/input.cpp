#include "wavepch.h"
#include "input.h"

namespace wave
{
	void input_handler::update(std::queue<std::unique_ptr<input_event>>& eventBuffer)
	{
		while (!eventBuffer.empty())
		{
			auto event = std::move(eventBuffer.front());
			eventBuffer.pop();

			switch (event.get()->get_type())
			{
			case input_event::type::KEY:
			{
				auto keyEvent = static_cast<key_event*>(event.get());
				m_key_states[keyEvent->get_key()] = keyEvent->get_action();
			}
			break;
			case input_event::type::MOUSE:
			{
				auto mouseEvent = static_cast<mouse_event*>(event.get());
				m_mouse_states[mouseEvent->get_button()] = mouseEvent->get_action();
			}
			break;
			case input_event::type::CURSOR:
			{
				auto cursorEvent = static_cast<cursor_event*>(event.get());
				m_cursor.translate(cursorEvent->get_x_pos(), cursorEvent->get_y_pos());
			}
			break;
			case input_event::type::SCROLL:
			{
				scroll_event* scrollEvent = static_cast<scroll_event*>(event.get());
				m_scroll.set(scrollEvent->get_x_offset(), scrollEvent->get_y_offset());
			}
			break;
			}
		}
	}

	void input_handler::flush()
	{
		m_cursor.reset();
		m_scroll.reset();
	}

	bool input_handler::is_key_pressed(int key)
	{
		return m_key_states[key] == GLFW_PRESS;
	}

	bool input_handler::is_key_repeat(int key)
	{
		return m_key_states[key] == GLFW_PRESS || m_key_states[key] == GLFW_REPEAT;
	}

	bool input_handler::is_key_released(int key)
	{
		return m_key_states[key] == GLFW_RELEASE;
	}

	bool input_handler::is_mouse_pressed(int button)
	{
		return m_mouse_states[button] == GLFW_PRESS;
	}

	bool input_handler::is_mouse_repeat(int button)
	{
		return m_mouse_states[button] == GLFW_PRESS || m_mouse_states[button] == GLFW_REPEAT;
	}

	bool input_handler::is_mouse_released(int button)
	{
		return m_mouse_states[button] == GLFW_RELEASE;
	}
}