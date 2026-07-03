#pragma once

#include "asterisk/Core/Common.h"
#include "asterisk/Core/SmartPointers.h"

#include "asterisk/Engine/Renderer/Color.h"

namespace asterisk {
	class ASTERISK_ENGINE_API RenderApi {
	public:
		enum Api {
			OpenGL,
			Vulkan,
			D3D11
		};

	private:
		static Api s_Api;

	public:
		// virtual methods
		virtual void Initialize() = 0;
		virtual void ClearScreen(const ColorRGBA& color) = 0;

	public:
		// static methods
		static Api GetApi();
		static void SetApi(Api api);

		static UniquePtr<RenderApi> Create();
	};
}

