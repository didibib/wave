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
    public:
        std::optional<GLuint> load(std::string filename);
    private:
        TextureManager();
    private:
        std::string mTextureDir;    
        std::unordered_map<GLuint, Texture> mTextureMap;
    private:
        void add_texture(GLuint id, uint width, uint height);
        void delete_texture(GLuint id);
    public:
        // C++ 11, We can use the better technique of deleting the methods we don't want.
        TextureManager(TextureManager const&) = delete;
        void operator=(TextureManager const&) = delete;
        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
    private:
        struct format
        {
        public:
            GLuint internal = 0;
            GLuint system = 0;
        };
        std::optional<format> GetFormat(FREE_IMAGE_FORMAT fif);
	};
}