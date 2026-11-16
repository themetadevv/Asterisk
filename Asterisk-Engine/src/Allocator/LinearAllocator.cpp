
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Allocator/LinearAllocator.h"

static bool is_power_of_two(uint32_t n) {
	return n != 0 && (n & (n - 1)) == 0;
}

static void* aligned_adjustment(const void* ptr, size_t alignment) {
	size_t mask = alignment - 1;
	size_t v = (reinterpret_cast<size_t>(ptr) + mask) & ~mask;
	return reinterpret_cast<void*>(v);
}

namespace asterisk {

	LinearAllocator::LinearAllocator(const std::string& name, size_t capacity) : 
		Allocator(name, capacity)
	{

	}

	void* LinearAllocator::Allocate(size_t size, uint32_t alignment) {
		RUNTIME_ASSERT(size > 0 && alignment > 0, "size < 0 || alignment < 0");
		RUNTIME_ASSERT(is_power_of_two(alignment), "Alignment must be power of two");

		void* current_ptr = m_Buffer + m_Offset;
		void* aligned_ptr = aligned_adjustment(current_ptr, alignment);
		
		size_t ptr_padding = reinterpret_cast<size_t>(aligned_ptr) - 
			reinterpret_cast<size_t>(current_ptr);

		size_t allocation_size = ptr_padding + size;
		RUNTIME_ASSERT(m_Offset + allocation_size <= m_Capacity, "Out of Memory!");

		m_Offset += allocation_size;
		m_Used = m_Offset;
		m_AllocCount++;

		ASTR_DEBUG(
			"Allocated '{}' bytes aligned '{}' in allocator '{}' of capacity '{}'.\n Used: {}",
			size, alignment, m_Name, m_Capacity, m_Used
		);
		
		return aligned_ptr;
	}

	void LinearAllocator::Reset() {
		m_Offset = 0;
		m_Used = 0;
		m_AllocCount = 0;
	}
}
