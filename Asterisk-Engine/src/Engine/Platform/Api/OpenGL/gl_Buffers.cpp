
#include "astpch.h"

#include "Core/Runtime.h"
#include "Logger/Logger.h"

#include "Engine/Platform/Api/OpenGL/gl_Debug.h"
#include "Engine/Platform/Api/OpenGL/gl_Buffers.h"

namespace asterisk {
	/*
		---------------
		VERTEX BUFFER
		---------------
	*/

	// dynamic
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(size_t buffer_data_size) {
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, buffer_data_size, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// static
	OpenGL_VertexBuffer::OpenGL_VertexBuffer(size_t buffer_data_size, const void* buffer_data) {
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, buffer_data_size, buffer_data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGL_VertexBuffer::~OpenGL_VertexBuffer() {
		if (m_BufferID) {
			glDeleteBuffers(1, &m_BufferID);
			m_BufferID = 0;
		}
	}

	void OpenGL_VertexBuffer::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGL_VertexBuffer::Unbind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGL_VertexBuffer::SetDataDynamic(size_t size, const void* data) {
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
		Unbind();
	}

	/*
		---------------
		INDEX BUFFER
		---------------
	*/

	OpenGL_IndexBuffer::OpenGL_IndexBuffer(uint32_t indices_count, const uint32_t* data) :
		m_IndicesCount(indices_count)
	{
		glGenBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_IndicesCount, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGL_IndexBuffer::~OpenGL_IndexBuffer() {
		if (m_BufferID) {
			glDeleteBuffers(1, &m_BufferID);
			m_BufferID = 0;
		}
	}

	void OpenGL_IndexBuffer::Bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGL_IndexBuffer::Unbind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
