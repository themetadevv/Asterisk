#pragma once

#include "Core/Common.h"

#include "Engine/Renderer/ImGuiRenderer.h"

namespace asterisk {
	class OpenGL_ImGuiRenderer : public ImGuiRenderer {
	public:
		void Initialize(NativeWindowHandle handle) override;
		void Shutdown() override;
		void NewFrame() override;
		void RenderDrawData() override;
	};
}

