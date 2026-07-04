
#include "astpch.h"

#include "Core/Constants.h"
#include "Core/Runtime.h"

#include "Logger/Logger.h"

#include "Engine/Platform/Api/OpenGL/gl_Debug.h"
#include "Engine/Platform/Api/OpenGL/gl_RenderContext.h"

namespace asterisk {
	OpenGL_RenderContext::OpenGL_RenderContext(const RenderContextData& _context_data) :
		m_RenderContextData(_context_data)
	{
		RUNTIME_ASSERT(
			m_RenderContextData.WindowHandle || m_RenderContextData.ProcessLoader,
			"[OpenGL_RenderContext] Window handle or gl process loader is null!"
		);

		int glad_init = gladLoadGLLoader((GLADloadproc)m_RenderContextData.ProcessLoader);
		RUNTIME_ASSERT(glad_init, "[OpenGL_RenderContext] Failed to load glad loader!");

		ASTR_INFO("Asterisk Engine");
		ASTR_INFO("Vendor: {}", (const char*)glGetString(GL_VENDOR));
		ASTR_INFO("Renderer: {}", (const char*)glGetString(GL_RENDERER));
		ASTR_INFO("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));

		GLint major = 0, minor = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		RUNTIME_ASSERT(
			major > ASTERISK_ENGINE_OPEN_GL_VERSION_MAJOR ||
			(major == ASTERISK_ENGINE_OPEN_GL_VERSION_MAJOR &&
				minor >= ASTERISK_ENGINE_OPEN_GL_VERSION_MINOR),
			"[OpenGL_RenderContext] OpenGL Version 4.6 Required for OpenGL Rendering!"
		);

		// debug ctx
		#ifdef GL_DEBUG
		GLint flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
		#endif

		std::cout << std::endl;
	}

	OpenGL_RenderContext::~OpenGL_RenderContext() {

	}

	void OpenGL_RenderContext::SetViewport(uint32_t width, uint32_t height) {
		glViewport(0, 0, width, height);
	}
}
