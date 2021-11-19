#include "pch/wavepch.h"
#include "event.h"
#include "event_handler.h"

namespace Wave
{
	EventHandler::EventHandler()
	{
		m_Cursor = std::make_unique<Cursor>();
		m_Scroll = std::make_unique<Scroll>();
	}
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
				m_Cursor->Translate(cursorEvent->GetXPos(), cursorEvent->GetYPos());
			}
			break;
			case Event::Type::Scroll:
			{
				ScrollEvent* scrollEvent = static_cast<ScrollEvent*>(event.get());
				m_Scroll->Set(scrollEvent->GetXOffset(), scrollEvent->GetYOffset());
			}
			break;
			case Event::Type::CursorEnter:
			{
				auto cursorEnterEvent = static_cast<CursorEnterEvent*>(event.get());
				m_Cursor->SetState(cursorEnterEvent->IsEntered());
			}
			break;
			case Event::Type::WindowFocus:
			{
				auto windowFocusEvent = static_cast<WindowFocusEvent*>(event.get());
				m_Cursor->SetState(windowFocusEvent->IsFocused());
			}
			break;
			}
		}
	}

	void EventHandler::Flush()
	{
		m_Cursor->Flush();
		m_Scroll->Flush();
	}

	Cursor& EventHandler::GetCursor() {
		return *m_Cursor; 
	}
	Scroll& EventHandler::GetScroll() {
		return *m_Scroll; 
	}

	bool EventHandler::IsKeyPressed(const int& key)
	{
		return m_KeyStates[key] == GLFW_PRESS;
	}

	bool EventHandler::IsKeyRepeat(const int& key)
	{
		return m_KeyStates[key] == GLFW_PRESS || m_KeyStates[key] == GLFW_REPEAT;
	}

	bool EventHandler::IsKeyReleased(const int& key)
	{
		return m_KeyStates[key] == GLFW_RELEASE;
	}

	bool EventHandler::IsMousePressed(const int& button)
	{
		return m_MouseStates[button] == GLFW_PRESS;
	}

	bool EventHandler::IsMouseRepeat(const int& button)
	{
		return m_MouseStates[button] == GLFW_PRESS || m_MouseStates[button] == GLFW_REPEAT;
	}

	bool EventHandler::IsMouseReleased(const int& button)
	{
		return m_MouseStates[button] == GLFW_RELEASE;
	}
}