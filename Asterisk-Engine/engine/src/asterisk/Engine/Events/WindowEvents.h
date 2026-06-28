#pragma once

#include "asterisk/Core/Common.h"

#include "asterisk/Engine/EventSystem/EventBase.h"

/*
	must be included after including the Engine/Window.h file
*/

namespace asterisk {
	// forward declare
	class Window;

	struct WindowEvent : public Event {
	private:
		Window* m_Window;

	public:
		WindowEvent(Window* _window) :
			m_Window(_window)
		{ }

		Window* GetWindow() const { return m_Window; }
	};

	struct WindowResizeEvent : public WindowEvent {
	private:
		uint32_t m_Width, m_Height;

	public:
		WindowResizeEvent(Window* _window, uint32_t _width, uint32_t _height) :
			WindowEvent(_window),
			m_Width(_width),
			m_Height(_height)
		{ }

		uint32_t GetWidth()  const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		DECLARE_EVENT(EventType::WindowResize)
	};

	struct WindowMoveEvent : public WindowEvent {
	private:
		uint32_t m_PosX, m_PosY;

	public:
		WindowMoveEvent(Window* _window, uint32_t _x, uint32_t _y) :
			WindowEvent(_window),
			m_PosX(_x),
			m_PosY(_y)
		{ }

		uint32_t GetPositionX() const { return m_PosX; }
		uint32_t GetPositionY() const { return m_PosY; }

		DECLARE_EVENT(EventType::WindowMove)
	};

	struct WindowMinimizeEvent : public WindowEvent {
	private:
		bool m_Minimized;

	public:
		WindowMinimizeEvent(Window* _window, bool _minimized) :
			WindowEvent(_window),
			m_Minimized(_minimized)
		{ }

		bool IsMinimized() const { return m_Minimized; }

		DECLARE_EVENT(EventType::WindowMinimize)
	};

	struct WindowCloseEvent : public WindowEvent {
	private:
		float m_ElapsedTime;

	public:
		WindowCloseEvent(Window* _window, float _ep_time) :
			WindowEvent(_window),
			m_ElapsedTime(_ep_time)
		{ }

		float GetElapsedTime() const { return m_ElapsedTime; }

		DECLARE_EVENT(EventType::WindowClose)
	};
}

