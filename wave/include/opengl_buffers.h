#pragma once

namespace wave
{
	class vertex_buffer
	{
	public:
		void create(std::vector<vertex> vertices);
		void create(std::vector<vertex> vertices, std::vector<int> indices);
		void draw();
	private:
		void bind();
		void unbind();
	private:
		int m_vertices_size;
		int m_indices_size;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;
	};
}