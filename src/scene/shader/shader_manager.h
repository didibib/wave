#pragma once

namespace Wave
{
    // https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	class ShaderManager
	{
    public:
        static ShaderManager& GetInstance()
        {
            // Guaranteed to be destroyed.
            // Instantiated on first use.
            static ShaderManager instance; 
            return instance;
        }
    private:
        ShaderManager() {
            const char* c_assets_dir = TOSTRING(ASSETS_DIR);
            std::string assets_dir(c_assets_dir);
            m_ShaderDir = assets_dir + "/shaders/";

            TRACE("Shader manager constructed");
        } // Constructor? (the {} brackets) are needed here.
    private:
        std::string m_ShaderDir;
    public:
        // C++ 11, We can use the better technique of deleting the methods we don't want.
        ShaderManager(ShaderManager const&) = delete;
        void operator=(ShaderManager const&) = delete;
        // Note: Scott Meyers mentions in his Effective Modern C++ book, 
        // that deleted functions should generally be public 
        // as it results in better error messages due to 
        // the compilers behavior to check accessibility before deleted status
	};
}