#pragma once

#include <string>

#include "Core/Common.h"

namespace asterisk {
	class ASTERISK_ENGINE_API Allocator {
	protected:
		std::string m_Name;

		char*  m_Buffer     = nullptr;
		size_t m_Capacity   = 0;
		size_t m_Used       = 0;
		size_t m_AllocCount = 0;

	public:
		// constructor
		Allocator(const std::string& name, const size_t& capacity) noexcept;
		~Allocator() noexcept;

		// delete copy constructor and copy assignment operator
		Allocator(const Allocator&) = delete;
		Allocator& operator=(const Allocator&) = delete;

		// move constructor and move assignment operator
		Allocator(Allocator&& newobj) noexcept;
		Allocator& operator=(Allocator&& newobj) noexcept;

	public:
		// debug
		const std::string& GetName() const { return m_Name; }

		// getters
		size_t GetCapacity()   const { return m_Capacity; }
		size_t GetUsed()       const { return m_Used; }
		size_t GetAllocCount() const { return m_AllocCount; }

	public:
		// virtual methods
		virtual void* Allocate(size_t size, uint32_t alignment) = 0;
		virtual void  Free(void* memory) {};

		virtual void Reset() = 0;
	};
}

