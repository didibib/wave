#include "pch/wavepch.h"
#include "mesh.h"

namespace Wave
{
	Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint>&& indices, std::vector<Texture>&& textures)
		: m_Vertices{ std::move(vertices) }, m_Indices{ std::move(indices) }, m_Textures{ std::move(textures) }
	{
		m_VertexBuffer.Create(m_Vertices, m_Indices);
	}

	void Mesh::Draw(Shader const& shader) const
	{
		m_VertexBuffer.Bind();

		m_VertexBuffer.Draw();

		m_VertexBuffer.Unbind();
	}
}