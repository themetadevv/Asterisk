
#include <asterisk/Engine/Window/Window.h>
#include <asterisk/Engine/Input/Input.h>
#include <asterisk/Logger/Logger.h>
#include <asterisk/Core/Runtime.h>

#include <asterisk/Math/Math.h>

#include <asterisk/Engine/EventSystem/EventManager.h>
#include <asterisk/Engine/Events/WindowEvents.h>

#include <asterisk/Engine/LayerSystem/LayerStack.h>

#include <asterisk/Engine/Layers/ImGuiLayer.h>
#include <asterisk/Engine/Renderer/RenderCommand.h>

#include <imgui.h>

int main() {
	asterisk::Logger::CreateLogger(ASTERISK_ENGINE_LOGGER_NAME);

	UniquePtr<asterisk::Window> window    = asterisk::Window::Create();
	UniquePtr<asterisk::LayerStack> stack = CreateUnique<asterisk::LayerStack>();

	bool running = true;
	asterisk::EventManager::SubscribeToEvent<asterisk::WindowCloseEvent>(
		[&](asterisk::Event& e) {
			auto& wce = asterisk::CastEvent<asterisk::WindowCloseEvent>(e);
			if (wce.GetWindow() == window.get()) {
				ASTR_INFO("Window Closed (elapsed time): {}", wce.GetElapsedTime());
				running = false;
			}
		}
	);

	asterisk::ImGuiLayer* imgui_layer = new asterisk::ImGuiLayer(window->GetHandle());
	stack->PushLayer(imgui_layer);

	asterisk::RenderCommand::InitializeRenderer();

	imgui_layer->OnAttach();
	ImGui::SetCurrentContext(imgui_layer->GetContext());

	while (running) {
		asterisk::RenderCommand::ClearColor(asterisk::ColorRGBA((uint8_t)45));

		imgui_layer->RenderImGui(
			[]() {
				ImGui::Begin("Test");

				ImGui::End();
			}
		);

		imgui_layer->OnUpdate(0.0f);
		imgui_layer->OnRender(0.0f);

		window->Update(0.0f);
	}
}