#include "pch/wavepch.h"
#include "mesh.h"

namespace Wave
{
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures)
	{
		m_Vertices = vertices;
		m_Indices = indices;
		m_Textures = textures;

		m_VertexBuffer.Create(m_Vertices, m_Indices);
	}

	void Mesh::Draw()
	{
		m_VertexBuffer.Bind();

		m_VertexBuffer.Draw();

		m_VertexBuffer.Unbind();
	}
}