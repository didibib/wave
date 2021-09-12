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

		Cursor& GetCursor() { return mCursor; }
		Scroll GetScroll() { return mScroll; }

		bool IsKeyPressed(int key);
		bool IsKeyRepeat(int key);
		bool IsKeyReleased(int key);

		bool IsMousePressed(int button);
		bool IsMouseRepeat(int button);
		bool IsMouseReleased(int button);
	private:
		Cursor mCursor;
		Scroll mScroll;
		std::map<int, int> mKeySates;
		std::map<int, int> mMouseStates;
	};
}