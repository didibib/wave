#pragma once 

namespace Wave
{
	class Event
	{
	public:
		enum class Type { Key, Mouse, Cursor, Scroll, CursorEnter, WindowFocus };
		Event(Type type) : m_Type(type) {}
	public:
		Type get_type() { return m_Type; }
	private:
		Type m_Type;
	};

	class KeyEvent : public Event
	{
	public:
		KeyEvent() = delete;
		KeyEvent(int key, int scancode, int action, int mods) :
			Event(Type::Key), m_Key(key), m_Scancode(scancode), m_Action(action), m_Mods(mods)
		{
		}
	public:
		int GetKey() { return m_Key; }
		int GetScancode() { return m_Scancode; }
		int getAction() { return m_Action; }
		int getMods() { return m_Mods; }
	private:
		int m_Key;
		int m_Scancode;
		int m_Action;
		int m_Mods;
	};

	class MouseEvent : public Event
	{
	public:
		MouseEvent() = delete;
		MouseEvent(int button, int action, int mods) :
			Event(Type::Mouse), m_Button(button), m_Action(action), m_Mods(mods)
		{
		}
		int GetButton() { return m_Button; }
		int GetAction() { return m_Action; }
		int GetMods() { return m_Mods; }
	private:
		int m_Button;
		int m_Action;
		int m_Mods;
	};

	class CursorEvent : public Event
	{
	public:
		CursorEvent() = delete;
		CursorEvent(float xPos, float yPos) :
			Event(Type::Cursor), m_XPos(xPos), m_YPos(yPos)
		{
		}
	public:
		float GetXPos() { return m_XPos; }
		float GetYPos() { return m_YPos; }
	private:
		float m_XPos;
		float m_YPos;
	};

	class ScrollEvent : public Event
	{
	public:
		ScrollEvent() = delete;
		ScrollEvent(float xOffset, float yOffset) :
			Event(Type::Scroll), m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}
	public:
		float GetXOffset() { return m_XOffset; }
		float GetYOffset() { return m_YOffset; }
	private:
		float m_XOffset;
		float m_YOffset;
	};

	class CursorEnterEvent : public Event
	{
	public:
		CursorEnterEvent() = delete;
		CursorEnterEvent(int entered) :
			Event(Type::CursorEnter), m_Entered(entered)
		{
		}
	public:
		bool IsEntered() { return m_Entered; }
	private:
		int m_Entered;
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = delete;
		WindowFocusEvent(int focused) :
			Event(Type::CursorEnter), m_Focused(focused)
		{
		}
	public:
		bool IsFocused() { return m_Focused; }
	private:
		int m_Focused;
	};

	class Cursor
	{
	public:
		glm::vec2 GetPosition() { return m_LastPos; }
		glm::vec2 GetOffset() { return m_Offset; }
	public:
		void Translate(double xPos, double yPos)
		{
			if (m_Reset)
			{
				m_LastPos.x = xPos;
				m_LastPos.y = yPos;
				m_Reset = false;
			}
			m_Offset.x = xPos - m_LastPos.x;
			// Reversed since y-coordinates go from bottom to top
			m_Offset.y = m_LastPos.y - yPos; 
			m_LastPos.x = xPos;
			m_LastPos.y = yPos;
		}
		void Flush()
		{
			m_Offset.x = 0;
			m_Offset.y = 0;
		}
		// [state] can be CursorEnter or WindowFocused.
		// We want to reset otherwise the offset can be to large.
		// For example when the users leaves the window from the left and enters from the right
		void SetState(int state)
		{
			m_Reset = state;
		}
	private:
		glm::vec2 m_LastPos;
		glm::vec2 m_Offset;
		bool m_Reset = true;
	};

	class Scroll
	{
	public:
		float GetXOffset() { return m_XOffset; }
		float GetYOffset() { return m_YOffset; }
		void Set(float xOffset, float yOffset)
		{
			m_XOffset = xOffset;
			m_YOffset = yOffset;
		}
		void Flush()
		{
			m_XOffset = 0;
			m_YOffset = 0;
		}
	private:
		float m_XOffset = 0;
		float m_YOffset = 0;
	};
}