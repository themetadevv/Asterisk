#pragma once

#include <string>

#include "Core/Common.h"

namespace asterisk::utils {
	ASTERISK_ENGINE_API std::string ReadFile(const std::string& path);
}

