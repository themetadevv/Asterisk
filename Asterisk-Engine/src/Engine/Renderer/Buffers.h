#pragma once

#include "Core/Common.h"

#include "Types/Containers.h"
#include "Types/SmartPointers.h"
#include "Types/String.h"

#include "Engine/Renderer/Enums.h"

namespace asterisk {
	struct BufferData {
		String Name;
		AttributeType Type;
		int ComponentCount;
		int Size;
		bool Normalized;
		size_t OffsetInMemory = 0;

		BufferData(StringView name, AttributeType type, bool normalize) :
			Name(name),
			Type(type),
			ComponentCount(AttributeComponentCount(type)),
			Size(AttributeSize(type)),
			Normalized(normalize)
		{ }
	};

	class ASTERISK_ENGINE_API BufferLayout {
	private:
		uint32_t m_Stride = 0;
		Vector<BufferData> m_BufferStorage;

	public:
		constexpr auto begin() { return m_BufferStorage.begin(); }
		constexpr auto end()   { return m_BufferStorage.end(); }

		constexpr auto cbegin() const { return m_BufferStorage.cbegin(); }
		constexpr auto cend()   const { return m_BufferStorage.cend(); }

	public:
		uint32_t GetStride() const { return m_Stride; }

	public:
		void AddBufferData(BufferData& data);
	};

	/*
		BUFFERS
	*/

	class ASTERISK_ENGINE_API VertexBuffer {
	protected:
		BufferLayout m_BufferLayout;

	public:
		void SetLayout(const BufferLayout& layout) { m_BufferLayout = layout; }
		const BufferLayout& GetBufferLayout() const { return m_BufferLayout; }

	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(size_t size, const void* data) = 0;

	public:
		static SharedPtr<VertexBuffer> Create(size_t buffer_data_size);
		static SharedPtr<VertexBuffer> Create(size_t buffer_data_size, const void* buffer_data);
	};

	class ASTERISK_ENGINE_API IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetIndicesCount() const = 0;

	public:
		static SharedPtr<IndexBuffer> Create(uint32_t indices_count, const uint32_t* data);
	};
}

