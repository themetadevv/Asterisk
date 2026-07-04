#pragma once

#include "Core/Common.h"

#include "Types/SmartPointers.h"

namespace asterisk {
	struct RenderContextData {
		void* WindowHandle  = nullptr;
		void* ProcessLoader = nullptr; // for opengl
	};

	class ASTERISK_ENGINE_API RenderContext {
	public:
		virtual ~RenderContext() = default;

		virtual void SetViewport(uint32_t width, uint32_t height) = 0;

	public:
		static UniquePtr<RenderContext> Create(const RenderContextData& _context_data);
	};
}

