
#include "astpch.h"

#include "Core/Constants.h"
#include "Core/Runtime.h"

#include "Logger/Logger.h"

#include "Engine/Layers/ImGuiLayer.h"

DISABLE_ALL_WARNING
#include <imgui.h>
#include <imgui_internal.h>
#include <ImGuizmo.h>
#include <GLFW/glfw3.h>
RESET_WARNING

namespace asterisk {
	ImGuiLayer::ImGuiLayer(NativeWindowHandle handle, const ImGuiSetting& setting) :
		Layer("ImGui Layer"),
		m_WindowHandle(handle),
		m_Setting(setting)
	{
		RUNTIME_ASSERT(m_WindowHandle, "[ImGuiLayer] WindowHandle is null!");
		m_ImGuiRenderer = ImGuiRenderer::Create();
	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::SetDockspace() {
		if (!m_Setting.Dockspace)
			return;

		ImGuiViewport* vp = ImGui::GetMainViewport();

		if (m_MenubarItemFn) {
			if (ImGui::BeginMainMenuBar()) {
				m_MenubarItemFn();
				ImGui::EndMainMenuBar();
			}
		}

		if (m_BottombarFn) {
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

			ImGuiWindowFlags flag = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings 
				| ImGuiWindowFlags_NoTitleBar 
				| ImGuiWindowFlags_NoResize;

			ImGui::BeginViewportSideBar(
				"##bottomBar",
				vp,
				ImGuiDir_Down,
				m_BottomBarHeight,
				flag
			);

			m_BottombarFn();

			ImGui::PopStyleVar(1);
			ImGui::End();
		}

		ImGuiWindowFlags dockspace_window_flags = 0;
		dockspace_window_flags |= ImGuiWindowFlags_NoDocking;
		dockspace_window_flags |= ImGuiWindowFlags_NoTitleBar;
		dockspace_window_flags |= ImGuiWindowFlags_NoCollapse;
		dockspace_window_flags |= ImGuiWindowFlags_NoResize;
		dockspace_window_flags |= ImGuiWindowFlags_NoMove;
		dockspace_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
		dockspace_window_flags |= ImGuiWindowFlags_NoNavFocus;
		dockspace_window_flags |= ImGuiWindowFlags_NoBackground;

		ImGui::SetNextWindowPos(vp->WorkPos);
		ImGui::SetNextWindowSize(vp->WorkSize);
		ImGui::SetNextWindowViewport(vp->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		ImGui::Begin("##mainDockspace", nullptr, dockspace_window_flags);

		ImGuiDockNodeFlags dockspace_flags = 0;
		dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;

		ImGuiID dockspace_id = ImGui::GetID("##mainDockspace");
		ImGui::DockSpace(dockspace_id, { 0, 0 }, dockspace_flags);

		ImGui::PopStyleVar(3);
		ImGui::End();
	}

	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		m_ImGuiContext = ImGui::CreateContext();

		auto& io = ImGui::GetIO();

		io.ConfigFlags |= m_Setting.MultiViewport ? ImGuiConfigFlags_ViewportsEnable : 0;
		io.ConfigFlags |= m_Setting.Dockspace ? ImGuiConfigFlags_DockingEnable : 0;
		io.ConfigFlags |= m_Setting.KeyboardNav ? ImGuiConfigFlags_NavEnableKeyboard : 0;
		io.ConfigFlags |= m_Setting.GamepadNav ? ImGuiConfigFlags_NavEnableGamepad : 0;

		switch (m_Setting.Theme) {
			case ImGuiSetting::ImGuiTheme::Dark: {
				ImGui::StyleColorsDark();
				break;
			}

			case ImGuiSetting::ImGuiTheme::Light: {
				ImGui::StyleColorsLight();
			}

			default: {
				break;
			}
		}

		io.ConfigWindowsMoveFromTitleBarOnly = m_Setting.WindowDragFromTitlebarOnly;

		m_ImGuiRenderer->Initialize(m_WindowHandle);
	}

	void ImGuiLayer::Begin() {
		m_ImGuiRenderer->NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

		SetDockspace();
	}

	void ImGuiLayer::End() {
		ImGui::Render();
		m_ImGuiRenderer->RenderDrawData();

		// multi viewport
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			GLFWwindow* main_ctx = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(main_ctx);
		}
	}

	void ImGuiLayer::OnDetach() {
		m_ImGuiRenderer->Shutdown();
		ImGui::DestroyContext();
	}
}
