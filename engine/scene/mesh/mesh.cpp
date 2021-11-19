#include "pch/wavepch.h"
#include "vertex_buffer.h"
#include "scene/shader/shader.h"
#include "mesh.h"

namespace Wave
{
	Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<std::shared_ptr<Texture>>&& textures, std::vector<uint>&& indices)
		: m_Vertices{ std::move(vertices) }, m_Indices{ std::move(indices) }, m_Textures{ std::move(textures) }
	{
		m_VertexBuffer = std::make_unique<VertexBuffer>();
		m_VertexBuffer->Create(m_Vertices, m_Indices);
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Draw(const Shader& shader) const
	{
		// Bind appropriate textures
		for (unsigned int i = 0; i < m_Textures.size(); i++)
		{
			std::string name = TextureTypeToString(m_Textures[i]->Type);

			// Now set the sampler to the correct texture unit
			// We asume we only have one texture for each type
			shader.SetInt(("u_Material." + name).c_str(), i);

			// And finally bind the texture
			glActiveTexture(GL_TEXTURE0 + i); 
			glBindTexture(GL_TEXTURE_2D, m_Textures[i]->Id);
		}
		m_VertexBuffer->Bind();
		m_VertexBuffer->Draw();
		m_VertexBuffer->Unbind();
	}
}