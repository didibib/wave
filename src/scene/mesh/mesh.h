#pragma once

namespace Wave
{
	class Mesh
	{
	public:
		Mesh() = delete;
		Mesh(std::vector<Vertex>&& vertices, std::vector<Texture>&& textures);
		Mesh(std::vector<Vertex>&& vertices, std::vector<uint>&& indices, std::vector<Texture>&& textures);
		void Draw(const Shader&) const;
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
		std::vector<Texture> m_Textures;
		VertexBuffer m_VertexBuffer;
	};
}