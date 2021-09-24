#include "pch/wavepch.h"
#include "event_handler.h"

namespace Wave
{
	void EventHandler::Update(std::queue<std::unique_ptr<Event>>& eventBuffer)
	{
		while (!eventBuffer.empty())
		{
			auto event = std::move(eventBuffer.front());
			eventBuffer.pop();

			switch (event.get()->get_type())
			{
			case Event::Type::Key:
			{
				auto keyEvent = static_cast<KeyEvent*>(event.get());
				m_KeyStates[keyEvent->GetKey()] = keyEvent->getAction();
			}
			break;
			case Event::Type::Mouse:
			{
				auto mouseEvent = static_cast<MouseEvent*>(event.get());
				m_MouseStates[mouseEvent->GetButton()] = mouseEvent->GetAction();
			}
			break;
			case Event::Type::Cursor:
			{
				auto cursorEvent = static_cast<CursorEvent*>(event.get());
				m_Cursor.Translate(cursorEvent->GetXPos(), cursorEvent->GetYPos());
			}
			break;
			case Event::Type::Scroll:
			{
				ScrollEvent* scrollEvent = static_cast<ScrollEvent*>(event.get());
				m_Scroll.Set(scrollEvent->GetXOffset(), scrollEvent->GetYOffset());
			}
			break;
			case Event::Type::CursorEnter:
			{
				auto cursorEnterEvent = static_cast<CursorEnterEvent*>(event.get());
				m_Cursor.SetState(cursorEnterEvent->IsEntered());
			}
			break;
			case Event::Type::WindowFocus:
			{
				auto windowFocusEvent = static_cast<WindowFocusEvent*>(event.get());
				m_Cursor.SetState(windowFocusEvent->IsFocused());
			}
			break;
			}
		}
	}

	void EventHandler::Flush()
	{
		m_Cursor.Flush();
		m_Scroll.Flush();
	}

	bool EventHandler::IsKeyPressed(int const& key)
	{
		return m_KeyStates[key] == GLFW_PRESS;
	}

	bool EventHandler::IsKeyRepeat(int const& key)
	{
		return m_KeyStates[key] == GLFW_PRESS || m_KeyStates[key] == GLFW_REPEAT;
	}

	bool EventHandler::IsKeyReleased(int const& key)
	{
		return m_KeyStates[key] == GLFW_RELEASE;
	}

	bool EventHandler::IsMousePressed(int const& button)
	{
		return m_MouseStates[button] == GLFW_PRESS;
	}

	bool EventHandler::IsMouseRepeat(int const& button)
	{
		return m_MouseStates[button] == GLFW_PRESS || m_MouseStates[button] == GLFW_REPEAT;
	}

	bool EventHandler::IsMouseReleased(int const& button)
	{
		return m_MouseStates[button] == GLFW_RELEASE;
	}
}