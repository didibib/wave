#pragma once 

namespace Wave
{
	class Shader;
	class Mesh;
	class Texture;

	class Model : public Object
	{
	public:
		void Load(const std::string& filepath);
		void Draw(const Shader&);

	private:
		void ProcessNode(aiNode*, const aiScene*);
		void ProcessMesh(aiMesh*, const aiScene*);
		void LoadMaterialTextures(aiMaterial*, std::vector<std::shared_ptr<Texture>>&, aiTextureType, TextureType);

	private:
		std::vector<std::unique_ptr<Mesh>> m_Meshes;
		std::string m_Directory;

	};
}