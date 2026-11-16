#pragma once

#include "Core/Common.h"

#include "Engine/Renderer/Buffers.h"

namespace asterisk {
	class OpenGL_VertexBuffer : public VertexBuffer {
	private:
		uint32_t m_BufferID;

	public:
		OpenGL_VertexBuffer(size_t buffer_data_size);
		OpenGL_VertexBuffer(size_t buffer_data_size, const void* buffer_data);
		~OpenGL_VertexBuffer() override;

	public:
		void Bind() override;
		void Unbind() override;

		void SetData(size_t size, const void* data) override;
	};

	class OpenGL_IndexBuffer : public IndexBuffer {
	private:
		uint32_t m_BufferID;
		uint32_t m_IndicesCount;

	public:
		OpenGL_IndexBuffer(uint32_t indices_count, const uint32_t* data);
		~OpenGL_IndexBuffer() override;

	public:
		void Bind() override;
		void Unbind() override;

		uint32_t GetIndicesCount() const override { return m_IndicesCount; }
	};
}

