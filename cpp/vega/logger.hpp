#pragma once

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace loggger {}

extern std::shared_ptr<spdlog::logger> logger;
