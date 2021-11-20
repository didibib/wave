#pragma once 

#include "util/singleton.h"

namespace Wave
{
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	class TextureManager 
	{
	public:
		static TextureManager& GetInstance()
		{
			// Guaranteed to be destroyed.
			// Instantiated on first use.
			static TextureManager instance;
			return instance;
		}
		std::optional<std::shared_ptr<Texture>> Load(const std::string& filepath, const TextureType&, const std::string& userKey = "");
		void Bind(const std::string& key, GLenum textureUnit);
		void Unbind();
		// Singleton requirements
		TextureManager(TextureManager const&) = delete;
		void operator=(TextureManager const&) = delete;
	protected:
		TextureManager() = default;

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureMap;
		void AddTexture(std::string key, std::shared_ptr<Texture>);
		void DeleteTexture(const std::string&);

	private:
		struct Format
		{
		public:
			GLuint internal = 0;
			GLuint system = 0;
		};
		std::optional<Format> GetFormat(const FREE_IMAGE_FORMAT fif);
	};
}