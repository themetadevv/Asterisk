#pragma once

/*
	Projects linking against this project must inlcude the spdlog directory
	This file should not be included by any headers in this project or face the consequences
*/

#include <string>
#include <memory>

#include "asterisk/Core/Common.h"
#include "asterisk/Core/Constants.h"

#include "asterisk/Logger/Formats.h"

DISABLE_ALL_WARNING
#include <spdlog/spdlog.h>
RESET_WARNING

#define DEFAULT_LOG_PATTERN "%^[%n] %v%$"

namespace asterisk {
	class ASTERISK_ENGINE_API logger {
	public:
		static void create_logger(
			const std::string& logger_name,
			const std::string& log_pattern = DEFAULT_LOG_PATTERN
		);

		static const std::shared_ptr<spdlog::logger>& get_logger(
			const std::string& logger_name
		);

		template <typename... Args>
		static void trace(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = get_logger(logger_name);
			if (!logger) return;

			logger->trace(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void info(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = get_logger(logger_name);
			if (!logger) return;
			logger->info(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void warn(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = get_logger(logger_name);
			if (!logger) return;
			logger->warn(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void error(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = get_logger(logger_name);
			if (!logger) return;
			logger->error(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void debug(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = get_logger(logger_name);
			if (!logger) return;
			logger->debug(fmt, std::forward<Args>(args)...);
		}
	};
}

#ifdef DEBUG_BUILD
	#define ASTR_TRACE(fmt, ...) ::asterisk::logger::trace(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_INFO(fmt, ...)  ::asterisk::logger::info(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_WARN(fmt, ...)  ::asterisk::logger::warn(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_ERROR(fmt, ...) ::asterisk::logger::error(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
#else
	#define ASTR_TRACE(...)
	#define ASTR_INFO(...)
	#define ASTR_WARN(...)
	#define ASTR_ERROR(...)
#endif