
#include "astpch.h"

#include "asterisk/Core/Runtime.h"
#include "asterisk/Logger/Logger.h"
#include "asterisk/Engine/Platform/Api/OpenGL/gl_Debug.h"

#if defined(GL_DEBUG)
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
		return;

	ASTR_WARN("API: OpenGL");

	switch (source) {
		case GL_DEBUG_SOURCE_API:             ASTR_WARN("Source: API"); break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   ASTR_WARN("Source: Window System"); break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: ASTR_WARN("Source: Shader Compiler"); break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     ASTR_WARN("Source: Third Party"); break;
		case GL_DEBUG_SOURCE_APPLICATION:     ASTR_WARN("Source: Application"); break;
		case GL_DEBUG_SOURCE_OTHER:           ASTR_WARN("Source: Other"); break;
	}

	switch (type)
	{
		case GL_DEBUG_TYPE_ERROR:               ASTR_WARN("Type: Error"); break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: ASTR_WARN("Type: Deprecated Behaviour"); break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  ASTR_WARN("Type: Undefined Behaviour"); break;
		case GL_DEBUG_TYPE_PORTABILITY:         ASTR_WARN("Type: Portability"); break;
		case GL_DEBUG_TYPE_PERFORMANCE:         ASTR_WARN("Type: Performance"); break;
		case GL_DEBUG_TYPE_MARKER:              ASTR_WARN("Type: Marker"); break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          ASTR_WARN("Type: Push Group"); break;
		case GL_DEBUG_TYPE_POP_GROUP:           ASTR_WARN("Type: Pop Group"); break;
		case GL_DEBUG_TYPE_OTHER:               ASTR_WARN("Type: Other"); break;
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH:         ASTR_ERROR("Severity: High"); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       ASTR_ERROR("Severity: Medium"); break;
	case GL_DEBUG_SEVERITY_LOW:          ASTR_ERROR("Severity: Low"); break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: ASTR_ERROR("Severity: Notification"); break;
	}

	ASTR_DEBUG("Debug message({}) : {}", id, message);
	std::cout << std::endl;
}
#endif
