
#include "astpch.h"

#include "Core/Runtime.h"
#include "Logger/Logger.h"

#include "Core/RandomNumGenerator.h"

namespace asterisk {
	static std::random_device s_randomDevice;
	static std::mt19937_64    s_Engine(s_randomDevice());

	static std::uniform_real_distribution<float>   s_float;
	static std::uniform_int_distribution<int>      s_int;
	static std::uniform_int_distribution<uint64_t> s_uint64_t;

	// float
	rand_float::rand_float() :
		m_Value(s_float(s_Engine))
	{ }

	// int
	rand_int::rand_int() :
		m_Value(s_int(s_Engine))
	{ }

	// uint64_t
	rand_uint64_t::rand_uint64_t() :
		m_Value(s_uint64_t(s_Engine))
	{ }
}
