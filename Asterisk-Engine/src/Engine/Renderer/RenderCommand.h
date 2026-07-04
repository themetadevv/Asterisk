#pragma once

#include "Core/Common.h"
#include "Types/Color.h"

namespace asterisk {
	class RenderCommand {
	public:
		static ASTERISK_ENGINE_API void InitializeRenderer();
		static ASTERISK_ENGINE_API void ClearColor(const ColorRGBA& color);
	};
}

