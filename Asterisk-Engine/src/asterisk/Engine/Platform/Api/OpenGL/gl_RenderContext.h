#pragma once

#include "asterisk/Core/Common.h"

#include "asterisk/Engine/Renderer/RenderContext.h"

namespace asterisk {
	class OpenGL_RenderContext : public RenderContext {
	private:
		RenderContextData m_RenderContextData;

	public:
		OpenGL_RenderContext(const RenderContextData& _context_data);
		~OpenGL_RenderContext() override;

		void SetViewport(uint32_t width, uint32_t height) override;
	};
}
