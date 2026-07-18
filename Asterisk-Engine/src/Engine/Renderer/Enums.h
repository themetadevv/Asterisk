#pragma once

#include <string>

namespace asterisk {
	enum class AttributeType {
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4
	};

	enum class ShaderType {
		Invalid = -1,
		Vertex,
		Fragment,
		Geometry
	};

	enum class ShaderStage {
		Invalid = -1,
		Compile,
		Link
	};

	int AttributeComponentCount(AttributeType type);
	int AttributeSize(AttributeType type);

	std::string ShaderTypeString(ShaderType type);
}