#include "pch/wavepch.h"
#include "texture.h"
#include "texture_manager.h"

namespace Wave
{
	TextureManager::TextureManager()
	{
		const char* c_assets_dir = TOSTRING(ASSETS_DIR);
		std::string assets_dir(c_assets_dir);
		mTextureDir = assets_dir + "/textures/";
		TRACE("Texture manager constructed");
	}

	std::optional<GLuint> TextureManager::Load(std::string filename)
	{		
		// wave_asset_dir is defined in wavepch.h
		std::string filepath = mTextureDir + filename;

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

		AddTexture(id, width, height);

		return id;
	}

	void TextureManager::Bind(GLuint id, GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void TextureManager::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureManager::AddTexture(GLuint id, uint width, uint height)
	{
		auto pair = std::pair<GLuint, Texture>(id, Texture(id, width, height));
		mTextureMap.insert(pair);
	}

	void TextureManager::DeleteTexture(GLuint id)
	{
		auto it = mTextureMap.find(id);
		if (it != mTextureMap.end())
		{
			mTextureMap.erase(it);
		}
	}

	std::optional<TextureManager::format> TextureManager::GetFormat(FREE_IMAGE_FORMAT fif)
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