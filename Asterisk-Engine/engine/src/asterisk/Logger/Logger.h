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
	class ASTERISK_ENGINE_API Logger {
	public:
		static void CreateLogger(
			const std::string& logger_name,
			const std::string& log_pattern = DEFAULT_LOG_PATTERN
		);

		static const std::shared_ptr<spdlog::logger>& GetLogger(
			const std::string& logger_name
		);

		template <typename... Args>
		static void Trace(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = GetLogger(logger_name);
			if (!logger) return;

			logger->trace(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void Info(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = GetLogger(logger_name);
			if (!logger) return;
			logger->info(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void Warn(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = GetLogger(logger_name);
			if (!logger) return;
			logger->warn(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void Error(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = GetLogger(logger_name);
			if (!logger) return;
			logger->error(fmt, std::forward<Args>(args)...);
		}

		template <typename... Args>
		static void Debug(
			const std::string& logger_name,
			fmt::format_string<Args...> fmt,
			Args&&... args
		) {
			auto logger = GetLogger(logger_name);
			if (!logger) return;
			logger->debug(fmt, std::forward<Args>(args)...);
		}
	};
}

#ifdef DEBUG_BUILD
	#define ASTR_TRACE(fmt, ...) ::asterisk::Logger::Trace(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_INFO(fmt, ...)  ::asterisk::Logger::Info(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_WARN(fmt, ...)  ::asterisk::Logger::Warn(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_ERROR(fmt, ...) ::asterisk::Logger::Error(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
	#define ASTR_DEBUG(fmt, ...) ::asterisk::Logger::Debug(ASTERISK_ENGINE_LOGGER_NAME, fmt, ##__VA_ARGS__)
#else
	#define ASTR_TRACE(...)
	#define ASTR_INFO(...)
	#define ASTR_WARN(...)
	#define ASTR_ERROR(...)
#endif