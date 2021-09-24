#pragma once

#include "vertex_buffer.h"

namespace Wave
{
	class Mesh
	{
	public:
		Mesh() = delete;
		Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<Texture> textures);
		void Draw();
	private:
		std::vector<Vertex> m_Vertices;
		std::vector<uint> m_Indices;
		std::vector<Texture> m_Textures;
		VertexBuffer m_VertexBuffer;
		GLuint m_VAO, m_VBO, m_EBO;
	};
}