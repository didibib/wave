#pragma once 

namespace Wave
{
	class Window;

	class WindowParams
	{
		friend Window;
	public:
		void SetWidth(int width)
		{
			mWidth = width;
		}

		void SetHeight(int height)
		{
			mHeight = height;
		}

		void SetTitle(const char* title)
		{
			mTitle = title;
		}

	private:
		int mWidth, mHeight;
		const char* mTitle;
	};
}