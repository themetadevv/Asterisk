
#include "astpch.h"

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#endif

#include "Core/NativeDialog.h"

namespace asterisk {
	static int ShowNativeMessageDialog(
		void* parent_window,
		const std::string& title,
		const std::string& msg,
		unsigned int type
	) {
		#ifdef PLATFORM_WINDOWS
		return MessageBoxA(
			static_cast<HWND>(parent_window),
			msg.c_str(),
			title.c_str(),
			(UINT)type
		);
		#else
		#error your platform is currently not supported.
		return 0;
		#endif
	}

	DialogResult ShowDialog(
		const std::string& title,
		const std::string& msg,
		DialogButtons buttons,
		DialogIcon icons,
		void* parent_window
	) {
		unsigned int type = 0;

		#ifdef PLATFORM_WINDOWS
		switch (buttons) {
			case DialogButtons::OK:
				type |= MB_OK; break;

			case DialogButtons::OKCancel:
				type |= MB_OKCANCEL; break;

			case DialogButtons::AbortRetryIgnore:
				type |= MB_ABORTRETRYIGNORE; break;

			case DialogButtons::YesNoCancel:
				type |= MB_YESNOCANCEL; break;

			case DialogButtons::YesNo:
				type |= MB_YESNO; break;

			case DialogButtons::RetryCancel:
				type |= MB_RETRYCANCEL; break;

			default:
				type |= 0; break;
			}

		switch (icons) {
			case DialogIcon::None:
				type |= 0; break;

			case DialogIcon::Info:
				type |= MB_ICONINFORMATION; break;

			case DialogIcon::Warning:
				type |= MB_ICONWARNING; break;

			case DialogIcon::Error:
				type |= MB_ICONERROR; break;

			case DialogIcon::Question:
				type |= MB_ICONQUESTION; break;

			default:
				type |= 0; break;
		}

		int r = ShowNativeMessageDialog(parent_window, title, msg, type);
		switch (r) {
			case IDOK:     return DialogResult::OK;
			case IDCANCEL: return DialogResult::Cancel;
			case IDABORT:  return DialogResult::Abort;
			case IDRETRY:  return DialogResult::Retry;
			case IDIGNORE: return DialogResult::Ignore;
			case IDYES:    return DialogResult::Yes;
			case IDNO:     return DialogResult::No;
			default:       return DialogResult::None;
		}
		#else
		#error your platform is currently not supported.
		#endif
	}

	DialogResult ShowErrorOccuredDialog(const std::string& msg, void* parent_window) {
		return ShowDialog("Error", msg, DialogButtons::OK, DialogIcon::Error, parent_window);
	}

	DialogResult ShowWarningDialog(const std::string& msg, void* parent_window) {
		return ShowDialog("Warning", msg, DialogButtons::OK, DialogIcon::Warning, parent_window);
	}

	void TerminateProgram() {
		#ifdef PLATFORM_WINDOWS
		TerminateProcess(GetCurrentProcess(), EXIT_FAILURE);
		#else
		#error your platform is currently not supported.
		#endif
	}
}
