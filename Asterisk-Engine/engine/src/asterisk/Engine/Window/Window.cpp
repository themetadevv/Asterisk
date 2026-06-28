
#include "astpch.h"

#include "asterisk/Core/Runtime.h"

#include "asterisk/Platform/Windows/WindowsWindow.h"
#include "asterisk/Engine/Window/Window.h"

namespace asterisk {
	UniquePtr<Window> Window::Create(const WindowProperty& _props) {
		#ifdef PLATFORM_WINDOWS
		return CreateUnique<WindowsWindow>(_props);
		#else
		#error your platform is currently not supported
		#endif
	}
}
