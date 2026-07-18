
#include "astpch.h"

#include "Core/Runtime.h"
#include "Logger/Logger.h"

#include "Engine/Renderer/RenderApi.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Platform/Api/OpenGL/gl_Shader.h"

namespace asterisk {

	SharedPtr<Shader> Shader::Create(const char* path, bool has_geometry) {
		switch (RenderApi::GetApi()) {
			case RenderApi::OpenGL: {
				return CreateShared<OpenGL_Shader>(path, has_geometry);
			}

			case RenderApi::Vulkan: {
				RUNTIME_ASSERT(false, "Vulkan is currently not supported by the engine!");
				return nullptr;
			}

			case RenderApi::D3D11: {
				RUNTIME_ASSERT(false, "D3D11 is currently not supported by the engine!");
				return nullptr;
			}

			default: {
				RUNTIME_ASSERT(false, "Unknown RenderApi selected!");
				return nullptr;
			}
		}
	}

}
