#include "pch/wavepch.h"
#include "texture_manager.h"

namespace Wave
{
	TextureManager::TextureManager()
	{
		const char* c_assets_dir = TOSTRING(ASSETS_DIR);
		std::string assets_dir(c_assets_dir);
		m_TextureDir = assets_dir + "/textures/";
		TRACE("Texture manager constructed");
	}

	std::optional<GLuint> TextureManager::Load(std::string const& filename, std::string const& key)
	{
		// wave_asset_dir is defined in wavepch.h
		std::string filepath = m_TextureDir + filename;

		const char* c_filepath = filepath.c_str();
		TRACE("Loading image: {}", c_filepath);

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileType(c_filepath);
		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(c_filepath);
		}
		if (fif == FIF_UNKNOWN)
		{
			ERROR("Failed to get filetype: {}", c_filepath);
			return false;
		}

		FIBITMAP* dib = FreeImage_Load(fif, c_filepath);
		if (!dib)
		{
			ERROR("Image failed to load: {}", c_filepath);
			return false;
		}

		byte* bits = FreeImage_GetBits(dib);
		uint width = FreeImage_GetWidth(dib);
		uint height = FreeImage_GetHeight(dib);

		TRACE("{} : [width:{}][height:{}]", c_filepath, width, height);
		if (bits == 0 || width == 0 || height == 0)
		{
			return false;
		}

		auto format = GetFormat(fif);
		if (!format)
		{
			ERROR("Unknown GL format: {}", c_filepath);
			return false;
		}

		uint id;
		glGenTextures(1, &id);
		if (id == 0)
		{
			ERROR("Failed to generate texture id");
			return false;
		}
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, (*format).internal, width, height, 0, (*format).system, GL_UNSIGNED_BYTE, bits);
		glGenerateMipmap(GL_TEXTURE_2D);

		FreeImage_Unload(dib);

		AddTexture(key, id, width, height);

		return id;
	}

	void TextureManager::Bind(std::string const& key, GLenum textureUnit)
	{
		auto it = m_TextureMap.find(key);
		if (it != m_TextureMap.end())
		{
			auto texture = (*it).second;
			glActiveTexture(textureUnit);
			glBindTexture(GL_TEXTURE_2D, texture.Id);
		}
	}

	void TextureManager::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureManager::AddTexture(std::string const& key, GLuint id, uint width, uint height)
	{
		auto pair = std::pair<std::string, Texture>(key, { id, width, height });
		m_TextureMap.insert(pair);
		TRACE("Added texture: {}", key);
	}

	void TextureManager::DeleteTexture(std::string const& key)
	{
		auto it = m_TextureMap.find(key);
		if (it != m_TextureMap.end())
		{
			m_TextureMap.erase(it);
		}
	}

	std::optional<TextureManager::Format> TextureManager::GetFormat(const FREE_IMAGE_FORMAT fif)
	{
		Format format;
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