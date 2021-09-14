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
		bool isBind;
		int mVerticesSize;
		int mIndicesSize;
		GLuint mVAO;
		GLuint mVBO;
		GLuint mEBO;
	};
}