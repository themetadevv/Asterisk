#pragma once

#include "asterisk/core/common.h"
#include "asterisk/Engine/EventSystem/EventBase.h"

namespace asterisk {
	struct WindowMinimizeEvent : public Event {
	private:
		bool m_Minimized;

	public:
		WindowMinimizeEvent(bool _minimized) :
			m_Minimized(_minimized)
		{ }

		bool IsMinimized() const { return m_Minimized; }

		DECLARE_EVENT(EventType::WindowMinimize)
	};
}

