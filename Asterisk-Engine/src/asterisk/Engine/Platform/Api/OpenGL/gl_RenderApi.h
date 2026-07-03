#pragma once

#include "asterisk/Core/Common.h"

#include "asterisk/Engine/Renderer/RenderApi.h"

namespace asterisk {
	class OpenGL_RenderApi : public RenderApi {
	public:
		void Initialize() override;
		void ClearScreen(const ColorRGBA& color) override;
	};
}

