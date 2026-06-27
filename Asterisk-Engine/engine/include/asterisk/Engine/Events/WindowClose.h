#pragma once

#include "asterisk/core/common.h"
#include "asterisk/Engine/EventSystem/EventBase.h"

namespace asterisk {
	struct WindowCloseEvent : public Event {
	private:
		float m_ElapsedTime;

	public:
		WindowCloseEvent(float _ep_time) :
			m_ElapsedTime(_ep_time)
		{ }

		float GetElapsedTime() const { return m_ElapsedTime; }

		DECLARE_EVENT(EventType::WindowClose)
	};
}

