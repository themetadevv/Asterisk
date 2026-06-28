
#include <asterisk/Engine/Window/Window.h>
#include <asterisk/Logger/Logger.h>
#include <asterisk/Core/Runtime.h>

#include <asterisk/Math/Math.h>

#include <asterisk/Engine/EventSystem/EventManager.h>
#include <asterisk/Engine/Events/WindowEvents.h>

int main() {
	asterisk::Logger::CreateLogger(ASTERISK_ENGINE_LOGGER_NAME);

	UniquePtr<asterisk::Window> window = asterisk::Window::Create();

	asterisk::EventManager::SubscribeToEvent<asterisk::WindowResizeEvent>(
		[&](asterisk::Event& e) {
			auto& wre = asterisk::CastEvent<asterisk::WindowResizeEvent>(e);
			if (wre.GetWindow() == window.get()) {
				ASTR_INFO("Window Size: {}x{}", wre.GetWidth(), wre.GetHeight());
			}
		}
	);

	asterisk::EventManager::SubscribeToEvent<asterisk::WindowMoveEvent>(
		[&](asterisk::Event& e) {
			auto& wme = asterisk::CastEvent<asterisk::WindowMoveEvent>(e);
			if (wme.GetWindow() == window.get()) {
				ASTR_INFO("Window Pos: {}x{}", wme.GetPositionX(), wme.GetPositionY());
			}
		}
	);

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

	while (running) {
		window->Update(0.0f);
	}

}