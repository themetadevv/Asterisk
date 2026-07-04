#pragma once

#include "Core/Common.h"

#if defined(BUILD_SHARED) || defined(BUILD_STATIC)
PUSH_WARNING
DISABLE_WARNING(4005)
#include <glad/glad.h>
RESET_WARNING
#endif

#if defined(DEBUG_BUILD)
#define GL_DEBUG
#endif

#ifdef GL_DEBUG
void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam
);
#endif