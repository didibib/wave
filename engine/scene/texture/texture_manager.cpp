#include "pch/wavepch.h"
#include "texture_manager.h"

namespace Wave
{
	std::optional<std::shared_ptr<Texture>> TextureManager::Load(const std::string& filepath, const TextureType& type, const std::string& userKey)
	{
		// Check if the texture is already loaded
		auto it = m_TextureMap.find(filepath);
		if (it != m_TextureMap.end())
		{
			return (*it).second;
		}

		const char* filepath_c = filepath.c_str();
		TRACE("Loading image: {}", filepath_c);

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		fif = FreeImage_GetFileType(filepath_c);
		if (fif == FIF_UNKNOWN)
		{
			fif = FreeImage_GetFIFFromFilename(filepath_c);
		}
		if (fif == FIF_UNKNOWN)
		{
			ERROR("Failed to get filetype: {}", filepath_c);
			return {};
		}

		FIBITMAP* dib = FreeImage_Load(fif, filepath_c);
		if (!dib)
		{
			ERROR("Image failed to load: {}", filepath_c);
			return {};
		}

		byte* bits = FreeImage_GetBits(dib);
		uint width = FreeImage_GetWidth(dib);
		uint height = FreeImage_GetHeight(dib);

		TRACE("{} : [width:{}][height:{}]", filepath_c, width, height);
		if (bits == 0 || width == 0 || height == 0)
		{
			return {};
		}

		auto format = GetFormat(fif);
		if (!format)
		{
			ERROR("Unknown GL format: {}", filepath_c);
			return {};
		}

		uint id = 0;
		glGenTextures(1, &id);
		if (id == 0)
		{
			ERROR("Failed to generate texture id");
			return {};
		}
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format.value().internal, width, height, 0, format.value().system, GL_UNSIGNED_BYTE, bits);
		glGenerateMipmap(GL_TEXTURE_2D);

		FreeImage_Unload(dib);

		// TODO: Remove this check when userKey is removed
		std::string key = filepath;
		if (userKey != "")
		{
			key = userKey;
		}		

		// Add texture
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(id, type, filepath, width, height);
		AddTexture(key, texture);

		return texture;
	}

	void TextureManager::Bind(const std::string& key, GLenum textureUnit)
	{
		auto it = m_TextureMap.find(key);
		if (it != m_TextureMap.end())
		{
			auto texture = (*it).second;
			glActiveTexture(textureUnit);
			glBindTexture(GL_TEXTURE_2D, texture->Id);
		}
	}

	void TextureManager::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureManager::AddTexture(std::string key, std::shared_ptr<Texture> texture)
	{
		auto pair = std::pair<std::string, std::shared_ptr<Texture>>(key, texture);
		m_TextureMap.insert(pair);
		TRACE("Added texture: {}", key);
	}

	void TextureManager::DeleteTexture(const std::string& key)
	{
		auto it = m_TextureMap.find(key);
		if (it != m_TextureMap.end())
		{
			m_TextureMap.erase(it);
			TRACE("Deleted texture: {}", key);
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