#pragma once

namespace Wave
{
	class Event;
	class Cursor;
	class Scroll;

	class EventHandler
	{
	public:
		EventHandler();
		void Update(std::queue<std::unique_ptr<Event>>& eventBuffer);
		void Flush();

		Cursor& GetCursor();
		Scroll& GetScroll();

		bool IsKeyPressed(const int& key);
		bool IsKeyRepeat(const int& key);
		bool IsKeyReleased(const int& key);

		bool IsMousePressed(const int& button);
		bool IsMouseRepeat(const int& button);
		bool IsMouseReleased(const int& button);
	private:
		std::unique_ptr<Cursor> m_Cursor;
		std::unique_ptr<Scroll> m_Scroll;
		std::map<int, int> m_KeyStates;
		std::map<int, int> m_MouseStates;
	};
}