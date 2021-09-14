#pragma once 

namespace Wave
{
	class Event
	{
	public:
		enum class Type { Key, Mouse, Cursor, Scroll, CursorEnter, WindowFocus };
		Event(Type type) : mType(type) {}
	public:
		Type get_type() { return mType; }
	private:
		Type mType;
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent() = delete;
		KeyEvent(int key, int scancode, int action, int mods) :
			Event(Type::Key), mKey(key), mScancode(scancode), mAction(action), mMods(mods)
		{
		}
	public:
		int GetKey() { return mKey; }
		int GetScancode() { return mScancode; }
		int getAction() { return mAction; }
		int getMods() { return mMods; }
	private:
		int mKey;
		int mScancode;
		int mAction;
		int mMods;
	};

	class MouseEvent : public Event
	{
	public:
		MouseEvent() = delete;
		MouseEvent(int button, int action, int mods) :
			Event(Type::Mouse), mButton(button), mAction(action), mMods(mods)
		{
		}
		int GetButton() { return mButton; }
		int GetAction() { return mAction; }
		int GetMods() { return mMods; }
	private:
		int mButton;
		int mAction;
		int mMods;
	};

	class CursorEvent : public Event
	{
	public:
		CursorEvent() = delete;
		CursorEvent(float xPos, float yPos) :
			Event(Type::Cursor), mXPos(xPos), mYPos(yPos)
		{
		}
	public:
		float GetXPos() { return mXPos; }
		float GetYPos() { return mYPos; }
	private:
		float mXPos;
		float mYPos;
	};

	class ScrollEvent : public Event
	{
	public:
		ScrollEvent() = delete;
		ScrollEvent(float xOffset, float yOffset) :
			Event(Type::Scroll), mXOffset(xOffset), mYOffset(yOffset)
		{
		}
	public:
		float GetXOffset() { return mXOffset; }
		float GetYOffset() { return mYOffset; }
	private:
		float mXOffset;
		float mYOffset;
	};

	class CursorEnterEvent : public Event
	{
	public:
		CursorEnterEvent() = delete;
		CursorEnterEvent(int entered) :
			Event(Type::CursorEnter), mEntered(entered)
		{
		}
	public:
		bool IsEntered() { return mEntered; }
	private:
		int mEntered;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = delete;
		WindowFocusEvent(int focused) :
			Event(Type::CursorEnter), mFocused(focused)
		{
		}
	public:
		bool IsFocused() { return mFocused; }
	private:
		int mFocused;
	};

	class Cursor
	{
	public:
		glm::vec2 GetPosition() { return mLastPos; }
		glm::vec2 GetOffset() { return mOffset; }
	public:
		void Translate(double xPos, double yPos)
		{
			if (mReset)
			{
				mLastPos.x = xPos;
				mLastPos.y = yPos;
				mReset = false;
			}
			mOffset.x = xPos - mLastPos.x;
			// Reversed since y-coordinates go from bottom to top
			mOffset.y = mLastPos.y - yPos; 
			mLastPos.x = xPos;
			mLastPos.y = yPos;
		}
		void Flush()
		{
			mOffset.x = 0;
			mOffset.y = 0;
		}
		// [state] can be CursorEnter or WindowFocused.
		// We want to reset otherwise the offset can be to large.
		// For example when the users leaves the window from the left and enters from the right
		void SetState(int state)
		{
			mReset = state;
		}
	private:
		glm::vec2 mLastPos;
		glm::vec2 mOffset;
		bool mReset = true;
	};

	class Scroll
	{
	public:
		float GetXOffset() { return mXOffset; }
		float GetYOffset() { return mYOffset; }
		void Set(float xOffset, float yOffset)
		{
			mXOffset = xOffset;
			mYOffset = yOffset;
		}
		void Flush()
		{
			mXOffset = 0;
			mYOffset = 0;
		}
	private:
		float mXOffset = 0;
		float mYOffset = 0;
	};
}