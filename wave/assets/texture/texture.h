#pragma once 

namespace Wave
{
	class Texture
	{
	public:
		Texture(GLuint id, uint width, uint height)
		{
			mId = id;
			mWidth = width;
			mHeight = height;
		}
	public:
		uint GetId(uint id) { return mId; }
		uint GetWidth(uint width) { return mWidth; }
		uint GetHeight(uint height) { return mHeight; }
	private:
		GLuint mId = 0;
		uint mWidth = 0;
		uint mHeight = 0;
	};
}