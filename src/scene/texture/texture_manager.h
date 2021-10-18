#pragma once 

namespace Wave
{
	// https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	class TextureManager : public Singleton<TextureManager>
	{
	public:
		// TODO: Remove userKey 
		std::optional<std::shared_ptr<Texture>> Load(const std::string& filepath, const TextureType&, const std::string& userKey = "");
		void Bind(const std::string& key, GLenum textureUnit);
		void Unbind();

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureMap;

	private:
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