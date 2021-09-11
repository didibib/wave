#pragma once

namespace Wave
{
	class VertexBuffer
	{
	public:
		void Create(std::vector<Vertex> vertices);
		void Create(std::vector<Vertex> vertices, std::vector<int> indices);
		void Draw();
	private:
		void Bind();
		void Unbind();
	private:
		int mVerticesSize;
		int mIndicesSize;
		GLuint mVAO;
		GLuint mVBO;
		GLuint mEBO;
	};
}