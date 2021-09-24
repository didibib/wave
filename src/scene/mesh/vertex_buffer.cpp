#include "pch/wavepch.h"
#include "vertex_buffer.h"

namespace Wave
{
	VertexBuffer::VertexBuffer() :
		m_IsBind(false), m_nVertices(0), m_nIndices(0), 
		m_VAO(0), m_VBO(0), m_EBO(0)
	{
	}

	void VertexBuffer::Create(std::vector<Vertex> vertices)
	{
		Create(vertices, std::vector<uint>());
	}

	void VertexBuffer::Create(std::vector<Vertex> vertices, std::vector<uint> indices)
	{
		m_nVertices = vertices.size();
		m_nIndices = indices.size();

		TRACE("Creating buffers : [vertices:{}][indices:{}]", m_nVertices, m_nIndices);

		// Generate buffers
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		// Bind buffers
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_nVertices, &vertices[0], GL_STATIC_DRAW);

		if (!indices.empty())
		{
			TRACE("Generating EBO");
			glGenBuffers(1, &m_EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_nIndices, &indices[0], GL_STATIC_DRAW);
		}
		// Set attributes
		// Position (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
		glEnableVertexAttribArray(0);
		// Color (location = 1)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
		glEnableVertexAttribArray(1);
		// UV (location = 2) 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Uv));
		glEnableVertexAttribArray(2);
		// Normal (location = 3
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(3);

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored
		glBindVertexArray(0);
	}

	void VertexBuffer::Bind()
	{
		glBindVertexArray(m_VAO);
		m_IsBind = true;
	}

	void VertexBuffer::Unbind()
	{
		glBindVertexArray(0);
		m_IsBind = false;
	}

	void VertexBuffer::Draw()
	{
		if (!m_IsBind)
		{
			ERROR("Forgot to bind the buffer");
		}
		if (m_EBO != 0)
		{
			glDrawElements(GL_TRIANGLES, m_nIndices, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_nVertices);
		}
	}
}