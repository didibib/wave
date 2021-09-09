#pragma once 

namespace wave
{
	class opengl_texture
	{
	public:
		bool load(std::string filename);
		void bind();
		void unbind();
	public:
		void set_id(uint id) { m_id = id; }
		void set_width(uint width) { m_width = width; }
		void set_height(uint height) { m_height = height; }

	private:
		uint m_id;
		uint m_width;
		uint m_height;
	private:		
		struct format
		{
		public:
			GLuint internal = 0;
			GLuint system = 0;
		};
		std::optional<format> get_format(FREE_IMAGE_FORMAT fif);
	};
}