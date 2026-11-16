
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Engine/Renderer/Enums.h"

namespace asterisk {
	int AttributeComponentCount(AttributeType type) {
		switch (type)
		{
			// 1 Component
			case AttributeType::Int:
			case AttributeType::Float:
			{
				return 1;
			}

			// 2 Component
			case AttributeType::Int2:
			case AttributeType::Float2:
			{
				return 2;
			}

			// 3 Component
			case AttributeType::Int3:
			case AttributeType::Float3:
			{
				return 3;
			}

			// 4 Component
			case AttributeType::Int4:
			case AttributeType::Float4:
			{
				return 4;
			}

			// Invalid Component
			default:
			{
				return 0;
			}
		}
	}

	int AttributeSize(AttributeType type) {
		switch (type)
		{
			// 1 Component Size
			case AttributeType::Int:
			case AttributeType::Float:
			{
				return 4;
			}

			// 2 Components Size
			case AttributeType::Int2:
			case AttributeType::Float2:
			{
				return 4 * 2;
			}

			// 3 Components Size
			case AttributeType::Int3:
			case AttributeType::Float3:
			{
				return 4 * 3;
			}

			// 4 Components Size
			case AttributeType::Int4:
			case AttributeType::Float4:
			{
				return 4 * 4;
			}

			// Invalid Components Size
			default:
			{
				return 0;
			}
		}
	}

	std::string ShaderTypeString(ShaderType type) {
		switch (type) {
			case ShaderType::Vertex:   return "Vertex";
			case ShaderType::Fragment: return "Fragment";
			case ShaderType::Geometry: return "Geometry";

			case ShaderType::Invalid:
			default: {
				return "Invalid";
			}
		}
	}

}
