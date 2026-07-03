#pragma once

#include <functional>

#include "asterisk/Core/Common.h"
#include "asterisk/Engine/LayerSystem/LayerBase.h"

#include "asterisk/Engine/Window/Window.h"
#include "asterisk/Engine/Renderer/ImGuiRenderer.h"

// forward declare
struct ImGuiContext;

namespace asterisk {
	struct ImGuiSetting {
		enum class ImGuiTheme {
			Light = 0,
			Dark
		};

		bool MultiViewport = false;
		bool Dockspace     = false;
		bool KeyboardNav   = false;
		bool GamepadNav    = false;

		bool WindowDragFromTitlebarOnly = true;

		ImGuiTheme Theme   = ImGuiTheme::Dark;
	};

	class ASTERISK_ENGINE_API ImGuiLayer : public Layer {
	private:
		NativeWindowHandle m_WindowHandle;
		ImGuiSetting m_Setting;

		UniquePtr<ImGuiRenderer> m_ImGuiRenderer;
		ImGuiContext* m_ImGuiContext = nullptr;

		using CallbackFn = std::function<void()>;

		float m_BottomBarHeight = 20.0f;

		CallbackFn m_MenubarItemFn;
		CallbackFn m_BottombarFn;
		CallbackFn m_RenderImGuiFn;

	public:
		ImGuiLayer(NativeWindowHandle handle, const ImGuiSetting& setting = ImGuiSetting());
		~ImGuiLayer() override;

		// getters
		ImGuiContext* GetContext() { return m_ImGuiContext; }

		// setters
		void SetupMenubar(const CallbackFn& fn) { 
			m_MenubarItemFn = fn; 
		}

		void SetupBottombar(float bar_height, const CallbackFn& fn) {
			m_BottomBarHeight = bar_height;
			m_BottombarFn = fn;
		}

	private:
		// private methods
		void SetDockspace();

	public:
		// methods
		void RenderImGui(const CallbackFn& fn) { m_RenderImGuiFn = fn; }

	public:
		// virtual methods
		void OnAttach() override;
		void OnUpdate(float dt) override;
		void OnRender(float dt) override;
		void OnDetach() override;
	};
}