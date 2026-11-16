
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Engine/Renderer/RenderApi.h"
#include "Engine/Renderer/Buffers.h"

#include "Engine/Platform/Api/OpenGL/gl_Buffers.h"

namespace asterisk {
	void BufferLayout::AddBufferData(BufferData& data) {
		m_BufferStorage.push_back(data);
		data.OffsetInMemory = m_Stride;
		m_Stride += data.Size;
	}

	SharedPtr<VertexBuffer> VertexBuffer::Create(size_t buffer_data_size) {
		switch (RenderApi::GetApi()) {
			case RenderApi::OpenGL: {
				return CreateShared<OpenGL_VertexBuffer>(buffer_data_size);
			}
				
			case RenderApi::Vulkan: {
				RUNTIME_ASSERT(false, "Vulkan is currently not supported by the engine!");
				return nullptr;
			}

			case RenderApi::D3D11: {
				RUNTIME_ASSERT(false, "D3D11 is currently not supported by the engine!");
				return nullptr;
			}

			default: {
				RUNTIME_ASSERT(false, "Unknown RenderApi selected!");
				return nullptr;
			}
		}
	}

	SharedPtr<VertexBuffer> VertexBuffer::Create(size_t buffer_data_size, const void* buffer_data) {
		switch (RenderApi::GetApi()) {
			case RenderApi::OpenGL: {
				return CreateShared<OpenGL_VertexBuffer>(buffer_data_size, buffer_data);
			}

			case RenderApi::Vulkan: {
				RUNTIME_ASSERT(false, "Vulkan is currently not supported by the engine!");
				return nullptr;
			}

			case RenderApi::D3D11: {
				RUNTIME_ASSERT(false, "D3D11 is currently not supported by the engine!");
				return nullptr;
			}

			default: {
				RUNTIME_ASSERT(false, "Unknown RenderApi selected!");
				return nullptr;
			}
		}
	}

	SharedPtr<IndexBuffer> IndexBuffer::Create(uint32_t indices_count, const uint32_t* data) {
		switch (RenderApi::GetApi()) {
			case RenderApi::OpenGL: {
				return CreateShared<OpenGL_IndexBuffer>(indices_count, data);
			}

			case RenderApi::Vulkan: {
				RUNTIME_ASSERT(false, "Vulkan is currently not supported by the engine!");
				return nullptr;
			}

			case RenderApi::D3D11: {
				RUNTIME_ASSERT(false, "D3D11 is currently not supported by the engine!");
				return nullptr;
			}

			default: {
				RUNTIME_ASSERT(false, "Unknown RenderApi selected!");
				return nullptr;
			}
		}
	}
}
