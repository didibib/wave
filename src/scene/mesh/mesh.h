#pragma once

namespace Wave
{
	class VertexBuffer;

	class Mesh
	{
	public:
		Mesh() = delete;
		Mesh(std::vector<Vertex>&& vertices, std::vector<std::shared_ptr<Texture>>&& textures, std::vector<uint>&& indices = {});
		~Mesh();
		void Draw(const Shader&) const;
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
		std::vector<std::shared_ptr<Texture>> m_Textures;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
	};
}