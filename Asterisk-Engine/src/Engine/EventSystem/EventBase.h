#pragma once

#include <string>
#include <type_traits>

#include "Core/Common.h"

namespace asterisk {
	enum class EventType {
		None = -1,
		WindowResize, WindowMove, WindowClose, WindowMinimize,
		KeyPress, KeyRelease,
		MousePress, MouseRelease, MouseScroll,
	};

	struct Event {
	public:
		bool Handled = false;

	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual std::string GetEventTypeString() const = 0;
	};

	template <typename T>
	inline T& CastEvent(Event& e) {
		static_assert(std::is_base_of_v<Event, T>, "T must derive from base 'Event' struct");
		return static_cast<T&>(e);
	}

#define DECLARE_EVENT(type) \
	virtual EventType GetEventType() const override { return type; } \
	virtual std::string GetEventTypeString() const override { return #type; } \
	static  EventType GetEventTypeStatic() { return type; }
}