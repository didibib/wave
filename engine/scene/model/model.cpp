#include "pch/wavepch.h"
#include "scene/shader/shader.h"
#include "scene/texture/texture.h"
#include "scene/texture/texture_manager.h"
#include "scene/mesh/vertex.h"
#include "scene/mesh/mesh.h"
#include "scene/object/object.h"
#include "model.h"

namespace Wave
{
	void Model::Load(const std::string& filepath)
	{
		TRACE("Loading model: {}", filepath);
		Assimp::Importer import;
		const aiScene* scene = import.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ERROR("Assimp import error: {}", import.GetErrorString());
			return;
		}
		m_Directory = filepath.substr(0, filepath.find_last_of('/')) + "/";
		TRACE("Model directory: {}", m_Directory);
		ProcessNode(scene->mRootNode, scene);
	}

	void Model::Draw(const Shader& shader)
	{
		shader.SetMat4("u_Model", GetModelMatrix());
		shader.SetMat4("u_NormalMatrix", GetNormalMatrix());

		for (uint i = 0; i < m_Meshes.size(); i++)
		{
			m_Meshes[i]->Draw(shader);
		}
	}

	void Model::ProcessNode(aiNode* aiNode, const aiScene* aiScene)
	{
		// Process all the node's meshes (if any)
		for (uint i = 0; i < aiNode->mNumMeshes; i++)
		{
			aiMesh* mesh = aiScene->mMeshes[aiNode->mMeshes[i]];
			ProcessMesh(mesh, aiScene);
		}
		// Then do the same for each of its children
		for (uint i = 0; i < aiNode->mNumChildren; i++)
		{
			ProcessNode(aiNode->mChildren[i], aiScene);
		}
	}

	void Model::ProcessMesh(aiMesh* aiMesh, const aiScene* aiScene)
	{
		// Process vertices
		std::vector<Vertex> vertices;
		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
		{
			Vertex vertex;
			// Process vertex position
			glm::vec3 vector;
			vector.x = aiMesh->mVertices[i].x;
			vector.y = aiMesh->mVertices[i].y;
			vector.z = aiMesh->mVertices[i].z;
			vertex.Position = vector;
			// Process vertex normals 
			vector.x = aiMesh->mNormals[i].x;
			vector.y = aiMesh->mNormals[i].y;
			vector.z = aiMesh->mNormals[i].z;
			vertex.Normal = vector;

			// Does the mesh contain texture coordinates?
			if (aiMesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				// Only use the first set of UVs
				vec.x = aiMesh->mTextureCoords[0][i].x;
				vec.y = aiMesh->mTextureCoords[0][i].y;
				vertex.UV = vec;
			}
			else
			{
				vertex.UV = glm::vec2(0.0f, 0.0f);
			}

			vertices.push_back(vertex);
		}

		// Process indices
		std::vector<uint> indices;
		for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
		{
			aiFace face = aiMesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		// Process material
		std::vector<std::shared_ptr<Texture>> textures;
		if (aiMesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = aiScene->mMaterials[aiMesh->mMaterialIndex];
			LoadMaterialTextures(material, textures, aiTextureType_DIFFUSE, TextureType::Diffuse);
			LoadMaterialTextures(material, textures, aiTextureType_SPECULAR, TextureType::Specular);
		}

		m_Meshes.push_back(std::make_unique<Mesh>(std::move(vertices), std::move(textures), std::move(indices)));
	}

	void Model::LoadMaterialTextures(aiMaterial* aiMaterial, std::vector<std::shared_ptr<Texture>>& textures, aiTextureType aiType, TextureType type)
	{
		for (unsigned int i = 0; i < aiMaterial->GetTextureCount(aiType); i++)
		{
			aiString filename;
			aiMaterial->GetTexture(aiType, i, &filename);
			std::string filepath = m_Directory + filename.C_Str();

			auto& tm = TextureManager::GetInstance();
			auto texture = tm.Load(filepath, type);
			if (texture)
			{
				textures.push_back(std::move(texture.value()));
			}
		}
	}
}