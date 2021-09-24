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

		bool IsKeyPressed(int const& key);
		bool IsKeyRepeat(int const& key);
		bool IsKeyReleased(int const& key);

		bool IsMousePressed(int const& button);
		bool IsMouseRepeat(int const& button);
		bool IsMouseReleased(int const& button);
	private:
		Cursor m_Cursor;
		Scroll m_Scroll;
		std::map<int, int> m_KeyStates;
		std::map<int, int> m_MouseStates;
	};
}