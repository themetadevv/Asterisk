#pragma once

#include "Core/Common.h"

namespace asterisk {
	class ASTERISK_ENGINE_API rand_float {
	private:
		float m_Value = 0.0f;

	public:
		rand_float();

		operator float() const {
			return m_Value;
		}
	};

	class ASTERISK_ENGINE_API rand_int {
	private:
		int m_Value = 0;

	public:
		rand_int();

		operator int() const {
			return m_Value;
		}
	};

	class ASTERISK_ENGINE_API rand_uint64_t {
	private:
		uint64_t m_Value = 0;

	public:
		rand_uint64_t();

		operator uint64_t() const {
			return m_Value;
		}
	};
}

