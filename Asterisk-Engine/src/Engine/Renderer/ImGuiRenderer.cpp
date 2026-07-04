
#include "astpch.h"

#include "Core/Runtime.h"

#include "Engine/Platform/Api/OpenGL/gl_ImGuiRenderer.h"
#include "Engine/Renderer/RenderApi.h"
#include "Engine/Renderer/ImGuiRenderer.h"

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
