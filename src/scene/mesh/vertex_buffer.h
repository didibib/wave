#pragma once

namespace Wave
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		void Create(std::vector<Vertex> const& vertices);
		void Create(std::vector<Vertex> const& vertices, std::vector<uint> const& indices);
		void Draw() const;
		void Bind() const;
		void Unbind() const;
	private:
		mutable bool m_IsBind;
		int m_nVertices;
		int m_nIndices;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
	};
}