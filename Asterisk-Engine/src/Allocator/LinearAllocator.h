#pragma once

#include "Core/Common.h"

#include "Allocator/AllocatorBase.h"

namespace asterisk {
	class ASTERISK_ENGINE_API LinearAllocator : public Allocator {
	private:
		size_t m_Offset = 0;

	public:
		LinearAllocator(const std::string& name, size_t capacity);

		void* Allocate(size_t size, uint32_t alignment) override;
		
		void Reset() override;
	};
}

