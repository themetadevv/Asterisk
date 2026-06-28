#pragma once

#include <string>

#include "asterisk/Core/Common.h"
#include "asterisk/Core/SmartPointers.h"

namespace asterisk {
	enum class WindowMode {
		Windowed = 0,
		WindowedFullscreen, 
		ExclusiveFullscreen
	};

	struct WindowProperty {
		std::string Title = "Window";
		uint32_t Width = 1366, Height = 768;
		WindowMode WinMode = WindowMode::Windowed;
		bool VSync  = true;
		bool Header = true;

		WindowProperty() = default;
	};

	using NativeWindowHandle = void*;

	class ASTERISK_ENGINE_API Window {
	public:
		virtual ~Window() = default;

	public:
		// getters
		virtual NativeWindowHandle GetHandle() const = 0;
		virtual const std::string& GetTitle() const = 0;

		virtual uint32_t GetWidth()  const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual WindowMode GetWindowMode() const = 0;

		virtual bool IsVSyncActive() const = 0;
		virtual bool IsHeaderRendered() const = 0;

		// setters
		virtual void SetTitle(const std::string& title) = 0;
		virtual void SetSize(uint32_t _w, uint32_t _h) = 0;
		virtual void SetWindowMode(WindowMode mode) = 0;

	public:
		// virtual methods
		virtual void Update(float dt) = 0;
		virtual void Close() = 0;

		// static methods
		static UniquePtr<Window> Create(const WindowProperty& _props = WindowProperty());
	};
}
