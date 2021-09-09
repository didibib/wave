#include "wavepch.h"
#include "opengl_buffers.h"

namespace wave
{
	void vertex_buffer::create(std::vector<vertex> vertices)
	{
		create(vertices, std::vector<int>());
	}

	void vertex_buffer::create(std::vector<vertex> vertices, std::vector<int> indices)
	{
		m_vertices_size = vertices.size();
		m_indices_size = indices.size();

		TRACE("Creating buffers : [vertices:{}][indices:{}]", m_vertices_size, m_indices_size);

		// Generate buffers
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		// Bind buffers
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * m_vertices_size, &vertices[0], GL_STATIC_DRAW);

		if (!indices.empty())
		{
			TRACE("Generating EBO");
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indices_size, &indices[0], GL_STATIC_DRAW);
		}
		// Set attributes
		// Position (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, position));
		glEnableVertexAttribArray(0);
		// Color (location = 1)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, color));
		glEnableVertexAttribArray(1);
		// UV (location = 2) 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, uv));
		glEnableVertexAttribArray(2);

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored
		glBindVertexArray(0);
	}

	void vertex_buffer::bind()
	{
		glBindVertexArray(m_VAO);
	}

	void vertex_buffer::unbind()
	{
		glBindVertexArray(0);
	}

	void vertex_buffer::draw()
	{
		bind();
		if (m_EBO != 0)
		{
			glDrawElements(GL_TRIANGLES, m_indices_size, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_vertices_size);
		}
		unbind();
	}
}