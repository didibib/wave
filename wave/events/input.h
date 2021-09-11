#pragma once

namespace Wave
{
	class InputHandler
	{
	public:
		class InputEvent
		{
		public:
			enum class Type { Key, Mouse, Cursor, Scroll };
			InputEvent(Type type) : mType(type) {}
		public:
			Type get_type() { return mType; }
		private:
			Type mType;
		};

		class KeyEvent : public InputEvent
		{
		public:
			KeyEvent() = delete;
			KeyEvent(int key, int scancode, int action, int mods) :
				InputEvent(Type::Key), mKey(key), mScancode(scancode), mAction(action), mMods(mods)
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

		class MouseEvent : public InputEvent
		{
		public:
			MouseEvent() = delete;
			MouseEvent(int button, int action, int mods) :
				InputEvent(Type::Mouse), mButton(button), mAction(action), mMods(mods)
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

		class CursorEvent : public InputEvent
		{
		public:
			CursorEvent() = delete;
			CursorEvent(float xPos, float yPos) :
				InputEvent(Type::Cursor), mXPos(xPos), mYPos(yPos)
			{
			}
		public:
			float GetXPos() { return mXPos; }
			float GetYPos() { return mYPos; }
		private:
			float mXPos;
			float mYPos;
		};

		class ScrollEvent : public InputEvent
		{
		public:
			ScrollEvent() = delete;
			ScrollEvent(float xOffset, float yOffset) :
				InputEvent(Type::Scroll), mXOffset(xOffset), mYOffset(yOffset)
			{
			}
		public:
			float GetXOffset() { return mXOffset; }
			float GetYOffset() { return mYOffset; }
		private:
			float mXOffset;
			float mYOffset;
		};

		class Cursor
		{
		public:
		public:
			void Translate(double xPos, double yPos)
			{
				if (mReset)
				{
					mXPos = xPos;
					mYPos = yPos;
					mReset = false;
				}
				mXOffset = xPos - mXPos;
				mYOffset = mYPos - yPos;
				mXPos = xPos;
				mYPos = yPos;
			}
			void Reset()
			{
				mXOffset = 0;
				mYOffset = 0;
			}
			void SetState(int state)
			{
				mReset = state;
			}
		private:
			double mXPos = 0;
			double mYPos = 0;
			double mXOffset = 0;
			double mYOffset = 0;
			bool mReset = false;
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
			void Reset()
			{
				mXOffset = 0;
				mYOffset = 0;
			}
		private:
			float mXOffset = 0;
			float mYOffset = 0;
		};

	public:
		InputHandler() = default;
		void Update(std::queue<std::unique_ptr<InputEvent>>& eventBuffer);
		void flush();

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