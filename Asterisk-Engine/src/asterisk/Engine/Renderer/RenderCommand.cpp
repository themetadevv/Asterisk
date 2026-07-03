
#include "astpch.h"

#include "asterisk/Core/Runtime.h"
#include "asterisk/Logger/Logger.h"

#include "asterisk/Engine/Renderer/RenderApi.h"
#include "asterisk/Engine/Renderer/RenderCommand.h"

namespace asterisk {
	static UniquePtr<RenderApi> s_RenderApi = RenderApi::Create();

	void RenderCommand::InitializeRenderer() {
		s_RenderApi->Initialize();
	}

	void RenderCommand::ClearColor(const ColorRGBA& color) {
		s_RenderApi->ClearScreen(color);
	}
}
