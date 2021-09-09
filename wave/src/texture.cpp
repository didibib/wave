#include "wavepch.h"
#include "FreeImage.h"
#include "texture.h"

namespace wave
{
	bool opengl_texture::load(std::string filename)
	{
		filename = "assets/textures/" + filename;
		const char* c_filename = filename.c_str();

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileType(c_filename);
		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(c_filename);
		}
		if (fif == FIF_UNKNOWN)
		{
			ERROR("Failed to get filetype: {}", c_filename);
			return false;
		}

		FIBITMAP* dib = FreeImage_Load(fif, c_filename);
		if (!dib)
		{
			ERROR("Image failed to load: {}", c_filename);
			return false;
		}

		byte* bits = FreeImage_GetBits(dib);
		m_width = FreeImage_GetWidth(dib);
		m_height = FreeImage_GetHeight(dib);
		
		if (bits == 0 || m_width == 0 || m_height == 0)
		{
			return false;
		}

		auto format = get_format(fif);
		if (!format)
		{
			ERROR("Unknown GL format: {}", c_filename);
			return false;
		}

		glGenTextures(1, &m_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, (*format).internal, m_width, m_height, 0, (*format).system, GL_UNSIGNED_BYTE, bits);
		glGenerateMipmap(GL_TEXTURE_2D);

		FreeImage_Unload(dib);
		return true;
	}

	void opengl_texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void opengl_texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	std::optional<opengl_texture::format> opengl_texture::get_format(FREE_IMAGE_FORMAT fif)
	{
		format format;
		switch (fif)
		{
		case FIF_JPEG:
		{
			format.internal = GL_RGB;
			format.system = GL_BGR;
		}
		break;
		case FIF_PNG:
		{
			format.internal = GL_RGBA;
			format.system = GL_BGRA;
		}
		break;
		default:
			return {};
		}
		return format;
	}
}