#pragma once

namespace Wave
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		void Create(std::vector<Vertex> vertices);
		void Create(std::vector<Vertex> vertices, std::vector<int> indices);
		void Draw();
		void Bind();
		void Unbind();

	private:
		bool m_IsBind;
		int m_nVertices;
		int m_nIndices;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
	};
}