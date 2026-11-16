
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Utils/Utils.h"

namespace asterisk {

	std::string utils::ReadFile(const std::string& path) {
		std::fstream file(path);
		if (!file.is_open())
			return "";

		std::stringstream buf;
		buf << file.rdbuf();

		return buf.str();
	}

}
