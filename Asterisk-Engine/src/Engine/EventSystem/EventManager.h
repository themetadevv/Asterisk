#pragma once

#include <functional>
#include <type_traits>

#include "Core/Common.h"

#include "Types/Containers.h"

#include "Engine/EventSystem/EventBase.h"

namespace asterisk {
	class EventManager {
	private:
		using EventCallback  = std::function<void(Event& e)>;

		struct EventListener {
			EventCallback Callback;
		};

		static ASTERISK_ENGINE_API UnorderedMap<EventType, Vector<EventListener>> s_EventListeners;

	public:
		template <typename T> 
		static void SubscribeToEvent(const EventCallback& fn) {
			static_assert(std::is_base_of_v<Event, T>, "T must derive from base 'Event' class");
			auto& listener = s_EventListeners[T::GetEventTypeStatic()];
			EventListener v = { fn };
			listener.push_back(std::move(v));
		}

		static ASTERISK_ENGINE_API void FireEvent(Event& e);
	};
}
