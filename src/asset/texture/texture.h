#pragma once 

namespace Wave
{
	class Texture
	{
	public:
		Texture(GLuint id, uint width, uint height)
		{
			m_Id = id;
			m_Width = width;
			m_Height = height;
		}
	public:
		uint GetId() { return m_Id; }
		uint GetWidth() { return m_Width; }
		uint GetHeight() { return m_Height; }
	private:
		GLuint m_Id = 0;
		uint m_Width = 0;
		uint m_Height = 0;
	};
}