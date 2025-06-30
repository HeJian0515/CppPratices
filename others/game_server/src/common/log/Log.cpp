#include "Log.h"

#include "LogDef.h"

using namespace HGS;
using namespace spdlog;

void HGS::SetLogLevel(LogLevel lev) {
    auto logLev = level::debug;
    switch (lev) {
        case LogLevel::Trace:
            logLev = level::trace;
            break;
        case LogLevel::Debug:
            logLev = level::debug;
            break;
        case LogLevel::Info:
            logLev = level::info;
            break;
        case LogLevel::Warning:
            logLev = level::warn;
            break;
        case LogLevel::Critical:
            logLev = level::critical;
            break;
        case LogLevel::Error:
            logLev = level::err;
            break;
    }
    spdlog::set_level(logLev);
}

void HGS::SetPattern(const std::string &pattern) {
    spdlog::set_pattern(pattern);
}

void HGS::LogTrace(const std::string &message) {
    spdlog::warn(message);
}

void HGS::LogWarning(const std::string &message) {
    spdlog::warn(message);
}

void HGS::LogInfo(const std::string &message) {
    spdlog::info(message);
}

void HGS::LogError(const std::string &message) {
    spdlog::error(message);
}

void HGS::LogDebug(const std::string &message) {
    spdlog::debug(message);
}
