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
				mKeySates[keyEvent->GetKey()] = keyEvent->getAction();
			}
			break;
			case Event::Type::Mouse:
			{
				auto mouseEvent = static_cast<MouseEvent*>(event.get());
				mMouseStates[mouseEvent->GetButton()] = mouseEvent->GetAction();
			}
			break;
			case Event::Type::Cursor:
			{
				auto cursorEvent = static_cast<CursorEvent*>(event.get());
				mCursor.Translate(cursorEvent->GetXPos(), cursorEvent->GetYPos());
			}
			break;
			case Event::Type::Scroll:
			{
				ScrollEvent* scrollEvent = static_cast<ScrollEvent*>(event.get());
				mScroll.Set(scrollEvent->GetXOffset(), scrollEvent->GetYOffset());
			}
			break;
			case Event::Type::CursorEnter:
			{
				auto cursorEnterEvent = static_cast<CursorEnterEvent*>(event.get());
				mCursor.SetState(cursorEnterEvent->IsEntered());
			}
			break;
			case Event::Type::WindowFocus:
			{
				auto windowFocusEvent = static_cast<WindowFocusEvent*>(event.get());
				mCursor.SetState(windowFocusEvent->IsFocused());
			}
			break;
			}
		}
	}

	void EventHandler::Flush()
	{
		mCursor.Flush();
		mScroll.Flush();
	}

	bool EventHandler::IsKeyPressed(int key)
	{
		return mKeySates[key] == GLFW_PRESS;
	}

	bool EventHandler::IsKeyRepeat(int key)
	{
		return mKeySates[key] == GLFW_PRESS || mKeySates[key] == GLFW_REPEAT;
	}

	bool EventHandler::IsKeyReleased(int key)
	{
		return mKeySates[key] == GLFW_RELEASE;
	}

	bool EventHandler::IsMousePressed(int button)
	{
		return mMouseStates[button] == GLFW_PRESS;
	}

	bool EventHandler::IsMouseRepeat(int button)
	{
		return mMouseStates[button] == GLFW_PRESS || mMouseStates[button] == GLFW_REPEAT;
	}

	bool EventHandler::IsMouseReleased(int button)
	{
		return mMouseStates[button] == GLFW_RELEASE;
	}
}