#include "pch/wavepch.h"
#include "input.h"

namespace Wave
{
	void InputHandler::Update(std::queue<std::unique_ptr<InputEvent>>& eventBuffer)
	{
		while (!eventBuffer.empty())
		{
			auto event = std::move(eventBuffer.front());
			eventBuffer.pop();

			switch (event.get()->get_type())
			{
			case InputEvent::Type::Key:
			{
				auto keyEvent = static_cast<KeyEvent*>(event.get());
				mKeySates[keyEvent->GetKey()] = keyEvent->getAction();
			}
			break;
			case InputEvent::Type::Mouse:
			{
				auto mouseEvent = static_cast<MouseEvent*>(event.get());
				mMouseStates[mouseEvent->GetButton()] = mouseEvent->GetAction();
			}
			break;
			case InputEvent::Type::Cursor:
			{
				auto cursorEvent = static_cast<CursorEvent*>(event.get());
				mCursor.Translate(cursorEvent->GetXPos(), cursorEvent->GetYPos());
			}
			break;
			case InputEvent::Type::Scroll:
			{
				ScrollEvent* scrollEvent = static_cast<ScrollEvent*>(event.get());
				mScroll.Set(scrollEvent->GetXOffset(), scrollEvent->GetYOffset());
			}
			break;
			}
		}
	}

	void InputHandler::flush()
	{
		mCursor.Reset();
		mScroll.Reset();
	}

	bool InputHandler::IsKeyPressed(int key)
	{
		return mKeySates[key] == GLFW_PRESS;
	}

	bool InputHandler::IsKeyRepeat(int key)
	{
		return mKeySates[key] == GLFW_PRESS || mKeySates[key] == GLFW_REPEAT;
	}

	bool InputHandler::IsKeyReleased(int key)
	{
		return mKeySates[key] == GLFW_RELEASE;
	}

	bool InputHandler::IsMousePressed(int button)
	{
		return mMouseStates[button] == GLFW_PRESS;
	}

	bool InputHandler::IsMouseRepeat(int button)
	{
		return mMouseStates[button] == GLFW_PRESS || mMouseStates[button] == GLFW_REPEAT;
	}

	bool InputHandler::IsMouseReleased(int button)
	{
		return mMouseStates[button] == GLFW_RELEASE;
	}
}