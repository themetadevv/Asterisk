
#include "astpch.h"

#include "asterisk/Core/Runtime.h"
#include "asterisk/Engine/Renderer/RenderContext.h"
#include "asterisk/Engine/Renderer/RenderApi.h"

#include "asterisk/Engine/Platform/Api/OpenGL/gl_RenderContext.h"

namespace asterisk {
	UniquePtr<RenderContext> RenderContext::Create(const RenderContextData& _context_data) {
		switch (RenderApi::GetApi()) {
			case RenderApi::OpenGL: {
				return CreateUnique<OpenGL_RenderContext>(_context_data);
				break;
			}

			case RenderApi::Vulkan: {
				RUNTIME_ASSERT(false, "[ImGuiLayer] No impl found for render api 'Vulkan'");
				return nullptr;
			}

			case RenderApi::D3D11: {
				RUNTIME_ASSERT(false, "[ImGuiLayer] No impl found for render api 'D3D11'");
				return nullptr;
			}

			default: {
				RUNTIME_ASSERT(false, "[ImGuiLayer] unknown render api");
				return nullptr;
			}
		}
	}
}
