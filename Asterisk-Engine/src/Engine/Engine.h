#pragma once

#define EDITOR_MODE

#include <string>

// Events
#include "Engine/Events/WindowEvents.h"

// Event System
#include "Engine/EventSystem/EventBase.h"
#include "Engine/EventSystem/EventManager.h"

// Input
#include "Engine/Input/Input.h"
#include "Engine/Input/InputCode.h"

// Layers
#ifdef EDITOR_MODE
#include "Engine/Layers/ImGuiLayer.h"
#endif

// Layer System
#include "Engine/LayerSystem/LayerBase.h"
#include "Engine/LayerSystem/LayerStack.h"

// Window
#include "Engine/Window/Window.h"

// Renderer
#include "Engine/Renderer/RenderApi.h"
#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Buffers.h"

namespace asterisk {
	struct EngineSetting {
		std::string Title = "Asterisk";
		bool VSync = true;
		bool CustomHeader = false;
	};

	class ASTERISK_ENGINE_API Engine {
	private:
		bool m_Running;
		EngineSetting m_Setting;

		UniquePtr<Window> m_MainWindow;
		UniquePtr<LayerStack> m_LayerStack;

		#ifdef EDITOR_MODE
		ImGuiLayer* m_ImGuiLayer = nullptr;
		#endif

		static Engine* s_Engine;

	public:
		Engine(const EngineSetting& _setting = EngineSetting());
		~Engine();

	private:
		void ProcessEvents();

	public:
		// getters
		Window&     GetMainWindow() const { return *m_MainWindow; }
		ImGuiLayer& GetImGuiLayer() const { return *m_ImGuiLayer; }

	public:
		// methods
		void PushLayer  (Layer* layer);
		void PushOverlay(Layer* overlay);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

	public:
		// engine
		void Run();
		void Close();

	public:
		// static accesors
		inline static Engine& Get() { return *s_Engine; }
	};

	Engine* Create();
}