
#include "astpch.h"

#include "asterisk/Core/Runtime.h"
#include "asterisk/Logger/Logger.h"

#include "asterisk/Engine/Platform/Api/OpenGL/gl_Debug.h"
#include "asterisk/Engine/Platform/Api/OpenGL/gl_RenderApi.h"

namespace asterisk {
	void OpenGL_RenderApi::Initialize() {
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGL_RenderApi::ClearScreen(const ColorRGBA& color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

}
