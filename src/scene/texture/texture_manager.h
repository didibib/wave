#pragma once 

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
		// TODO: Remove userKey 
		std::optional<std::shared_ptr<Texture>> Load(const std::string& filepath, const TextureType&, const std::string& userKey = "");
		void Bind(const std::string& key, GLenum textureUnit);
		void Unbind();

	private:
		TextureManager() {};
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_TextureMap;

	private:
		void AddTexture(std::string key, std::shared_ptr<Texture>);
		void DeleteTexture(const std::string&);

	public:
		// C++ 11, We can use the better technique of deleting the methods we don't want.
		TextureManager(const TextureManager&) = delete;
		void operator=(const TextureManager&) = delete;
		// Note: Scott Meyers mentions in his Effective Modern
		//       C++ book, that deleted functions should generally
		//       be public as it results in better error messages
		//       due to the compilers behavior to check accessibility
		//       before deleted status

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