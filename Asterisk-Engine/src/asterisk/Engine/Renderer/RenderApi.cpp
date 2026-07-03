
#include "astpch.h"

#include "asterisk/Core/Runtime.h"

#include "asterisk/Engine/Renderer/RenderApi.h"
#include "asterisk/Engine/Platform/Api/OpenGL/gl_RenderApi.h"

namespace asterisk {
	// default render api
	RenderApi::Api RenderApi::s_Api = RenderApi::OpenGL;

	RenderApi::Api RenderApi::GetApi() {
		return s_Api;
	}

	void RenderApi::SetApi(Api api) {
		s_Api = api;
	}

	UniquePtr<RenderApi> RenderApi::Create() {
		switch (s_Api) {
			case RenderApi::OpenGL: {
				return CreateUnique<OpenGL_RenderApi>();
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
