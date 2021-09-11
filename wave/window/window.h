#pragma once

namespace Wave
{
	class Window
	{
	public:
		Window(int width, int height, const char* title) {
			Log::Init();
			mWidth = width;
			mHeight = height;
			mTitle = title;
		}
		~Window()
		{
			Log::Shutdown();
		}
	public:
		virtual void Run() = 0;
		virtual void* GetNativeWindow() = 0;
	public:
		int GetWidth() { return mWidth; }
		int GetHeight() { return mHeight; }
		std::string GetTitle() { return mTitle; }
	protected:
		int mWidth;
		int mHeight;
		std::string mTitle;
	};
}