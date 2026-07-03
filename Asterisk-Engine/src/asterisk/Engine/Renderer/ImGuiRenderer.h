#pragma once

#include "asterisk/Core/Common.h"
#include "asterisk/Core/SmartPointers.h"
#include "asterisk/Engine/Window/Window.h"

namespace asterisk {
	class ImGuiRenderer {
	public:
		virtual void Initialize(NativeWindowHandle handle) = 0;
		virtual void Shutdown() = 0;

		virtual void NewFrame() = 0;
		virtual void RenderDrawData() = 0;

	public:
		static UniquePtr<ImGuiRenderer> Create();
	};
}

