
#include "astpch.h"

#include "Core/Runtime.h"
#include "Logger/Logger.h"

#include "Engine/EventSystem/EventManager.h"
#include "Engine/Events/WindowEvents.h"

#include "Engine/Platform/Windows/WindowsWindow.h"

DISABLE_ALL_WARNING
#include <GLFW/glfw3.h>
RESET_WARNING

namespace asterisk {
	WindowsWindow::WindowsWindow(const WindowProperty& _props) :
		m_Property(_props)
	{
		glfwSetErrorCallback(
			[](int error_code, const char* description) {
				ASTR_ERROR("[WindowsWindow] glfw error: {0}, '{1}'", error_code, description);
			}
		);

		int glfw_status = glfwInit();
		RUNTIME_ASSERT(glfw_status, "[WindowsWindow] glfw failed to initialize!");

		glfwWindowHint(GLFW_DECORATED, m_Property.CustomHeader ? 0 : 1);

		// renderer api initalization
		// .......
		// .......

		m_Handle = glfwCreateWindow(
			(int)m_Property.Width,
			(int)m_Property.Height,
			m_Property.Title.c_str(),
			nullptr, nullptr
		);

		RUNTIME_ASSERT(m_Handle, "[WindowsWindow] glfwCreateWindow returned null!");
		m_PrimaryMonitorHandle = static_cast<void*>(glfwGetPrimaryMonitor());

		// renderer context initalization
		// .......
		// .......

		glfwMakeContextCurrent(m_Handle);
		m_RenderContext = RenderContext::Create({ m_Handle, glfwGetProcAddress });

		glfwSwapInterval(m_Property.VSync ? 1 : 0);
		glfwSetWindowUserPointer(m_Handle, this);

		// process events
		// .......
		// .......

		ProcessWindowEvents();
		ProcessInputEvents();

		Input::Initialize();
	}

	WindowsWindow::~WindowsWindow() {
		if (m_Handle) {
			glfwDestroyWindow(m_Handle);
			glfwTerminate();
			m_Handle = nullptr;
		}
	}

	void WindowsWindow::ProcessWindowEvents() {
		// window resize event
		glfwSetWindowSizeCallback(
			m_Handle, 
			[](GLFWwindow* window, int width, int height) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

				_this->m_Property.Width  = width;
				_this->m_Property.Height = height;

				WindowResizeEvent e(_this, (uint32_t)width, (uint32_t)height);
				EventManager::FireEvent(e);
			}
		);

		// window move event
		glfwSetWindowPosCallback(
			m_Handle,
			[](GLFWwindow* window, int x, int y) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

				WindowMoveEvent e(_this, (uint32_t)x, (uint32_t)y);
				EventManager::FireEvent(e);
			}
		);

		// window minimize event
		glfwSetWindowIconifyCallback(
			m_Handle,
			[](GLFWwindow* window, int iconified) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

				WindowMinimizeEvent e(_this, (bool)iconified);
				EventManager::FireEvent(e);
			}
		);

		// window close event
		glfwSetWindowCloseCallback(
			m_Handle,
			[](GLFWwindow* window) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				
				WindowCloseEvent e(_this, (float)glfwGetTime());
				EventManager::FireEvent(e);
			}
		);

		// window focus loss event
		glfwSetWindowFocusCallback(
			m_Handle,
			[](GLFWwindow* window, int focused) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				if (focused == 0) {
					Input::ClearInput();
				}
			}
		);

		// framebuffer resize event
		glfwSetFramebufferSizeCallback(
			m_Handle,
			[](GLFWwindow* window, int width, int height) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
				_this->m_RenderContext->SetViewport((int)width, (int)height);
			}
		);
	}

	void WindowsWindow::ProcessInputEvents() {
		// key event
		glfwSetKeyCallback(
			m_Handle,
			[](GLFWwindow* window, int key, int scancode, int action, int mods) {
				auto _this = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));

				switch (action) {
					case GLFW_PRESS: {
						Input::OnKeyPressInternal((KeyCode)key);
						break;
					}

					case GLFW_RELEASE: {
						Input::OnKeyReleasedInternal((KeyCode)key);
						break;
					}
				}
			}
		);

		// mouse button event 
		glfwSetMouseButtonCallback(
			m_Handle,
			[](GLFWwindow* window, int button, int action, int mods) {
				switch (action) {
					case GLFW_PRESS: {
						Input::OnMousePressInternal((MouseCode)button);
						break;
					}

					case GLFW_RELEASE: {
						Input::OnMouseReleasedInternal((MouseCode)button);
						break;
					}
				}
			}
		);
	}

	NativeWindowHandle WindowsWindow::GetHandle() const {
		return static_cast<NativeWindowHandle>(m_Handle);
	}

	const std::string& WindowsWindow::GetTitle() const {
		return m_Property.Title;
	}

	uint32_t WindowsWindow::GetWidth() const {
		return m_Property.Width;
	}

	uint32_t WindowsWindow::GetHeight() const {
		return m_Property.Height;
	}

	WindowMode WindowsWindow::GetWindowMode() const {
		return m_Property.WinMode;
	}

	bool WindowsWindow::IsVSyncActive() const {
		return m_Property.VSync;
	}

	bool WindowsWindow::IsHeaderRendered() const {
		return m_Property.CustomHeader;
	}

	void WindowsWindow::SetTitle(const std::string& title) {
		m_Property.Title = title;
		glfwSetWindowTitle(m_Handle, title.c_str());
	}

	void WindowsWindow::SetSize(uint32_t _w, uint32_t _h) {
		m_Property.Width  = _w;
		m_Property.Height = _h;
		glfwSetWindowSize(m_Handle, _w, _h);
	}

	void WindowsWindow::SetWindowMode(WindowMode mode) {

	}

	void WindowsWindow::Update(float dt) {
		Input::Update();
		glfwSwapBuffers(m_Handle);
		glfwPollEvents();
	}

	void WindowsWindow::Close() {
		glfwSetWindowShouldClose(m_Handle, true);
	}
}
