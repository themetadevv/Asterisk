
#include <asterisk/Engine/window/window.h>
#include <asterisk/Logger/Logger.h>
#include <asterisk/Core/Runtime.h>

#include <asterisk/Math/Math.h>

#include <asterisk/Engine/EventSystem/EventManager.h>
#include <asterisk/Engine/Events/WindowResize.h>

int main() {
	asterisk::logger::create_logger(ASTERISK_ENGINE_LOGGER_NAME);

	asterisk::WindowResizeEvent e(900, 600);

	asterisk::EventManager::SubscribeToEvent<asterisk::WindowResizeEvent>([](asterisk::Event& e) {
		auto& event = asterisk::CastEvent<asterisk::WindowResizeEvent>(e);
		ASTR_INFO("Window Size: {}, {}", event.GetWidth(), event.GetHeight());
	});

	asterisk::EventManager::FireEvent(e);

	while (true);
}