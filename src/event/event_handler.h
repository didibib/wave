#pragma once

#include "event.h"

namespace Wave
{
	class EventHandler
	{
	public:
		EventHandler() = default;
		void Update(std::queue<std::unique_ptr<Event>>& eventBuffer);
		void Flush();

		Cursor& GetCursor() { return m_Cursor; }
		Scroll GetScroll() { return m_Scroll; }

		bool IsKeyPressed(int key);
		bool IsKeyRepeat(int key);
		bool IsKeyReleased(int key);

		bool IsMousePressed(int button);
		bool IsMouseRepeat(int button);
		bool IsMouseReleased(int button);
	private:
		Cursor m_Cursor;
		Scroll m_Scroll;
		std::map<int, int> m_KeyStates;
		std::map<int, int> m_MouseStates;
	};
}