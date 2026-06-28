
#include "astpch.h"

#include "asterisk/Logger/Logger.h"

DISABLE_ALL_WARNING
#include <spdlog/sinks/stdout_color_sinks.h>
RESET_WARNING

namespace asterisk {
	static std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::stdout_color_sink_mt>> s_loggerSink;
	static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> s_loggers;

	void Logger::CreateLogger(const std::string& logger_name, const std::string& log_pattern) {
		if (s_loggers.contains(logger_name))
			return;

		// setting up sink
		auto log_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		log_sink->set_pattern(log_pattern.empty() ? DEFAULT_LOG_PATTERN : log_pattern);
		s_loggerSink.try_emplace(logger_name, std::move(log_sink));

		// creating the logger
		std::shared_ptr logger = std::make_shared<spdlog::logger>(
			logger_name,
			s_loggerSink.at(logger_name)
		);

		spdlog::register_logger(logger);
		logger->set_level(spdlog::level::trace);
		logger->flush_on(spdlog::level::trace);

		s_loggers.try_emplace(logger_name, std::move(logger));
	}

	const std::shared_ptr<spdlog::logger>& Logger::GetLogger(const std::string& logger_name) {
		auto it = s_loggers.find(logger_name);
		if (it == s_loggers.end())
			throw std::runtime_error("[Logger] logger not found " + logger_name);
		
		return it->second;
	}
}
