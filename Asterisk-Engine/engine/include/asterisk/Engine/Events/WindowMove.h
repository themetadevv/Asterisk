#pragma once

#include "asterisk/core/common.h"
#include "asterisk/Engine/EventSystem/EventBase.h"

namespace asterisk {
	struct WindowMoveEvent : public Event {
	private:
		uint32_t m_PosX, m_PosY;

	public:
		WindowMoveEvent(uint32_t _x, uint32_t _y) :
			m_PosX(_x), m_PosY(_y)
		{ }

		uint32_t GetPositionX() const { return m_PosX; }
		uint32_t GetPositionY() const { return m_PosY; }

		DECLARE_EVENT(EventType::WindowMove)
	};
}

