#pragma once

#include "Core/Common.h"

#include "Types/SmartPointers.h"

#include "Engine/Window/Window.h"

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

