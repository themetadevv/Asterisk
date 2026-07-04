
#include "astpch.h"

#include "EventManager.h"

namespace asterisk {
	UnorderedMap<EventType, Vector<EventManager::EventListener>> EventManager::s_EventListeners;
	
	void EventManager::FireEvent(Event& e) {
		auto it = s_EventListeners.find(e.GetEventType());
		if (it == s_EventListeners.end())
			return;

		for (auto& listener : it->second) {
			if (e.Handled)
				break;

			listener.Callback(e);
		}
	}

}
