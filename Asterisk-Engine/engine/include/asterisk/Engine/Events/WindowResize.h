#pragma once

#include "asterisk/core/common.h"
#include "asterisk/Engine/EventSystem/EventBase.h"

namespace asterisk {
	struct WindowResizeEvent : public Event {
	private:
		uint32_t m_Width, m_Height;

	public:
		WindowResizeEvent(uint32_t _width, uint32_t _height) :
			m_Width(_width), m_Height(_height)
		{ }

		uint32_t GetWidth()  const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		DECLARE_EVENT(EventType::WindowResize)
	};
}

