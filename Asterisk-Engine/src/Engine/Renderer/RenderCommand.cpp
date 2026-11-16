
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Engine/Renderer/RenderApi.h"
#include "Engine/Renderer/RenderCommand.h"

namespace asterisk {
	static UniquePtr<RenderApi> s_RenderApi = RenderApi::Create();

	void RenderCommand::InitializeRenderer() {
		s_RenderApi->Initialize();
	}

	void RenderCommand::ClearColor(const ColorRGBA& color) {
		s_RenderApi->ClearScreen(color);
	}
}
