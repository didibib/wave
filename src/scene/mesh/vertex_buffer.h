#pragma once

namespace Wave
{
	class VertexBuffer
	{
	public:
		VertexBuffer();
		void Create(const std::vector<Vertex>& vertices);
		void Create(const std::vector<Vertex>& vertices, const std::vector<uint>& indices);
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