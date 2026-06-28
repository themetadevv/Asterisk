#pragma once

#include "asterisk/Core/Common.h"

#include "asterisk/Engine/Window/Window.h"
#include "asterisk/Engine/Input/Input.h"

// forward declare
struct GLFWwindow;

namespace asterisk {

	class WindowsWindow final : public Window, Input {
	private:
		GLFWwindow* m_Handle         = nullptr;
		void* m_PrimaryMonitorHandle = nullptr;

		WindowProperty m_Property;

	public:
		WindowsWindow(const WindowProperty& _props);
		~WindowsWindow() override;

	private:
		void ProcessWindowEvents();
		void ProcessInputEvents();

	public:
		// getters
		NativeWindowHandle GetHandle() const override;
		const std::string& GetTitle() const override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;

		WindowMode GetWindowMode() const override;

		// setters
		bool IsVSyncActive() const override;
		bool IsHeaderRendered() const override;

		void SetTitle(const std::string& title) override;
		void SetSize(uint32_t _w, uint32_t _h) override;
		void SetWindowMode(WindowMode mode) override;

	public:
		// methods
		void Update(float dt) override;
		void Close() override;
	};
}

