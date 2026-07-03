#pragma once

#include "asterisk/Core/Common.h"

#include "asterisk/Engine/Renderer/Color.h"

namespace asterisk {
	class RenderCommand {
	public:
		static ASTERISK_ENGINE_API void InitializeRenderer();
		static ASTERISK_ENGINE_API void ClearColor(const ColorRGBA& color);
	};
}

