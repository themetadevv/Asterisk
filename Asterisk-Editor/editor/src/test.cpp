
#include <asterisk/Engine/Window/Window.h>
#include <asterisk/Engine/Input/Input.h>
#include <asterisk/Logger/Logger.h>
#include <asterisk/Core/Runtime.h>

#include <asterisk/Math/Math.h>

#include <asterisk/Engine/EventSystem/EventManager.h>
#include <asterisk/Engine/Events/WindowEvents.h>

int main() {
	asterisk::Logger::CreateLogger(ASTERISK_ENGINE_LOGGER_NAME);

	UniquePtr<asterisk::Window> window = asterisk::Window::Create();

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