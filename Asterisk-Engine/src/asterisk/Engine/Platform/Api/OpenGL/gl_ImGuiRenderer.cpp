
#include "astpch.h"

#include "asterisk/Core/Constants.h"
#include "asterisk/Engine/Platform/Api/OpenGL/gl_ImGuiRenderer.h"

DISABLE_ALL_WARNING
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
RESET_WARNING

namespace asterisk {
	void OpenGL_ImGuiRenderer::Initialize(NativeWindowHandle handle) {
		ImGui_ImplGlfw_InitForOpenGL(reinterpret_cast<GLFWwindow*>(handle), true);
		ImGui_ImplOpenGL3_Init(ASTERISK_ENGINE_OPEN_GL_VERSION);
	}

	void OpenGL_ImGuiRenderer::Shutdown() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
	}

	void OpenGL_ImGuiRenderer::NewFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
	}

	void OpenGL_ImGuiRenderer::RenderDrawData() {
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
