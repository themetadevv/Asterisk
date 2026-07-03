
#include "astpch.h"

#include "asterisk/Core/Runtime.h"

#include "asterisk/Engine/Renderer/ImGuiRenderer.h"
#include "asterisk/Engine/Renderer/RenderApi.h"

#include "asterisk/Engine/Platform/Api/OpenGL/gl_ImGuiRenderer.h"

namespace asterisk {
	UniquePtr<ImGuiRenderer> ImGuiRenderer::Create() {
		switch (RenderApi::GetApi()) {
			case RenderApi::OpenGL: {
				return CreateUnique<OpenGL_ImGuiRenderer>();
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
