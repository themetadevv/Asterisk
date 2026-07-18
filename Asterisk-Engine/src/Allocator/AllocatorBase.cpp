
#include "astpch.h"

#include "Core/Runtime.h"
#include "Logger/Logger.h"

#include "Allocator/AllocatorBase.h"

namespace asterisk {
	Allocator::Allocator(const std::string& name, const size_t& capacity) noexcept 
		: m_Name(name), m_Capacity(capacity)
	{
		m_Buffer = (char*) ::operator new(m_Capacity);
	}

	Allocator::~Allocator() noexcept {
		::operator delete(m_Buffer);
	}

	Allocator::Allocator(Allocator&& newobj) noexcept {
		std::exchange(newobj.m_Name, "");
		std::exchange(newobj.m_Buffer, nullptr);
		std::exchange(newobj.m_Capacity, 0);
		std::exchange(newobj.m_Used, 0);
		std::exchange(newobj.m_AllocCount, 0);
	}

	Allocator& Allocator::operator=(Allocator&& newobj) noexcept {
		if (this == &newobj)
			return *this;

		delete[] m_Buffer;

		std::exchange(newobj.m_Name, "");
		std::exchange(newobj.m_Buffer, nullptr);
		std::exchange(newobj.m_Capacity, 0);
		std::exchange(newobj.m_Used, 0);
		std::exchange(newobj.m_AllocCount, 0);

		return *this;
	}

}
