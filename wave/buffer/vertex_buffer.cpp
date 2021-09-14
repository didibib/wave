#include "pch/wavepch.h"
#include "vertex_buffer.h"

namespace Wave
{
	VertexBuffer::VertexBuffer() :
		isBind(false), mVerticesSize(0), mIndicesSize(0), 
		mVAO(0), mVBO(0), mEBO(0)
	{
	}

	void VertexBuffer::Create(std::vector<Vertex> vertices)
	{
		Create(vertices, std::vector<int>());
	}

	void VertexBuffer::Create(std::vector<Vertex> vertices, std::vector<int> indices)
	{
		mVerticesSize = vertices.size();
		mIndicesSize = indices.size();

		TRACE("Creating buffers : [vertices:{}][indices:{}]", mVerticesSize, mIndicesSize);

		// Generate buffers
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		// Bind buffers
		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVerticesSize, &vertices[0], GL_STATIC_DRAW);

		if (!indices.empty())
		{
			TRACE("Generating EBO");
			glGenBuffers(1, &mEBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * mIndicesSize, &indices[0], GL_STATIC_DRAW);
		}
		// Set attributes
		// Position (location = 0)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);
		// Color (location = 1)
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);
		// UV (location = 2) 
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
		glEnableVertexAttribArray(2);
		// Normal (location = 3
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		// Unbind buffers
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored
		glBindVertexArray(0);
	}

	void VertexBuffer::Bind()
	{
		glBindVertexArray(mVAO);
		isBind = true;
	}

	void VertexBuffer::Unbind()
	{
		glBindVertexArray(0);
		isBind = false;
	}

	void VertexBuffer::Draw()
	{
		if (!isBind)
		{
			ERROR("Forgot to bind the buffer");
		}
		if (mEBO != 0)
		{
			glDrawElements(GL_TRIANGLES, mIndicesSize, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, mVerticesSize);
		}
	}
}