
#include "astpch.h"

#include "Core/NativeDialog.h"
#include "Logger/Logger.h"

#include "Engine/Engine.h"

namespace asterisk {
	Engine* Engine::s_Engine = nullptr;

	Engine::Engine(const EngineSetting& _setting) :
		m_Running(true),
		m_Setting(_setting)
	{
		s_Engine = this;

		// Logger initialization
		// .......
		// .......

		Logger::CreateLogger(ASTERISK_ENGINE_LOGGER_NAME);

		// Main Window initialization
		// .........
		// .........

		WindowProperty window_property;
		window_property.Title  = m_Setting.Title;
		window_property.VSync  = m_Setting.VSync;
		window_property.CustomHeader = m_Setting.CustomHeader;

		m_MainWindow = Window::Create(window_property);

		// LayerStack initialization
		// .........
		// .........

		m_LayerStack = CreateUnique<LayerStack>();

		// ImGuiLayer initialization
		// .........
		// .........

		ImGuiSetting imgui_setting;
		imgui_setting.Theme         = ImGuiSetting::ImGuiTheme::Dark;
		imgui_setting.Dockspace     = true;
		imgui_setting.KeyboardNav   = true;
		imgui_setting.GamepadNav    = false;
		imgui_setting.MultiViewport = false;
		imgui_setting.WindowDragFromTitlebarOnly = true;

		m_ImGuiLayer = new ImGuiLayer(m_MainWindow->GetHandle(), imgui_setting);
		PushOverlay(m_ImGuiLayer);

		ProcessEvents();
	}

	Engine::~Engine() {

	}

	void Engine::ProcessEvents() {
		EventManager::SubscribeToEvent<WindowCloseEvent>(
			[&](Event& e) {
				auto& event = CastEvent<WindowCloseEvent>(e);
				if (event.GetWindow() == m_MainWindow.get()) {
					Close();
				}
			}
		);
	}

	void Engine::PushLayer(Layer* layer) {
		m_LayerStack->PushLayer(layer);
		layer->OnAttach();
	}

	void Engine::PushOverlay(Layer* overlay) {
		m_LayerStack->PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Engine::PopLayer(Layer* layer) {
		m_LayerStack->PopLayer(layer);
	}

	void Engine::PopOverlay(Layer* overlay) {
		m_LayerStack->PopOverlay(overlay);
	}

	void Engine::Run() {
		while (m_Running) {
			float dt = 0.0f;
			RenderCommand::ClearColor({ 45, 45, 45 });

			m_ImGuiLayer->Begin();

			for (Layer* layers : *m_LayerStack) {
				layers->OnUpdate(dt);
				layers->OnRender(dt);
			}

			m_ImGuiLayer->End();

			m_MainWindow->Update(dt);
		}
	}

	void Engine::Close() {
		m_Running = false;
	}

}
