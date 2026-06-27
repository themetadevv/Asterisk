#pragma once

#include <string>
#include <format>

#include "asterisk/Core/Common.h"

namespace asterisk {
	enum class DialogButtons {
		OK,
		OKCancel,
		AbortRetryIgnore,
		YesNoCancel,
		YesNo,
		RetryCancel
	};

	enum class DialogResult {
		None = 0,
		OK, Cancel,
		Abort, Retry, Ignore,
		Yes, No
	};

	enum class DialogIcon {
		None = 0,
		Info,
		Warning,
		Error,
		Question
	};

	ASTERISK_ENGINE_API DialogResult ShowDialog(
		const std::string& title,
		const std::string& msg,
		DialogButtons buttons,
		DialogIcon icons,
		void* parent_window = nullptr
	);

	ASTERISK_ENGINE_API DialogResult ShowErrorOccuredDialog(
		const std::string& msg,
		void* parent_window = nullptr
	);

	ASTERISK_ENGINE_API DialogResult ShowWarningDialog(
		const std::string& msg, 
		void* parent_window = nullptr
	);

	ASTERISK_ENGINE_API void TerminateProgramOnFailure();
}

#ifdef DEBUG_BUILD

#define ASTR_RUNTIME_ASSERT(expr, ...)                                         \
    do {                                                                       \
        while (!(expr)) {                                                      \
            std::string msg = std::format(                                     \
                "Assertion failed!\n"                                          \
                "Expression: {}\n"                                             \
                "File: {}\n"                                                   \
                "Line: {}\n"                                                   \
                "Message: {}\n",                                               \
                #expr, __FILE__, __LINE__, __VA_ARGS__);                       \
                                                                               \
            ::asterisk::DialogResult result = ::asterisk::ShowDialog(          \
                "Asterisk Assertion",                                          \
                msg,                                                           \
                ::asterisk::DialogButtons::AbortRetryIgnore,                   \
                ::asterisk::DialogIcon::Error,                                 \
                nullptr);                                                      \
                                                                               \
            switch (result) {                                                  \
                case ::asterisk::DialogResult::Abort:                          \
                    ::asterisk::TerminateProgramOnFailure(); break;            \
                                                                               \
                case ::asterisk::DialogResult::Retry:                          \
                    DEBUG_BREAK; break;										   \
                                                                               \
                case ::asterisk::DialogResult::Ignore:                         \
                    goto runtime_assert_end;                                   \
                                                                               \
                default:                                                       \
                    goto runtime_assert_end;                                   \
            }                                                                  \
        }                                                                      \
        runtime_assert_end:;                                                   \
    } while (false)

#else
#define runtime_assert(...)
#endif